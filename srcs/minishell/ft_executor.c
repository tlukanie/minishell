/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:11:29 by okraus            #+#    #+#             */
/*   Updated: 2023/08/05 19:49:24 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//test local path then test variable
static char	*ft_pathjoin(char *path, char *cmd)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_calloc(ft_strlen(path) + 2 + ft_strlen(cmd), sizeof(char));
	while (path[i])
	{
		str[i] = path[i];
		i++;
	}
	str[i] = '/';
	i++;
	while (cmd[j])
	{
		str[i + j] = cmd[j];
		j++;
	}
	return (str);
}

static int	ft_exec(t_ms *ms, char **cmd)
{
	int		i;
	int		fail;
	char	*cmdp;
	char	**paths;
	char	**env;

	i = 0;
	fail = 1;
	env = ft_list2split(ms->el);
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, env);
	paths = ft_getenvvals(ms, "PATH");
	if (!paths)
		return (fail);
	while (paths[i])
	{
		cmdp = ft_pathjoin(paths[i], cmd[0]);
		if (access(cmdp, X_OK) == 0)
			execve(cmdp, cmd, env);
		free(cmdp);
		i++;
	}
	ft_printf_fd(2, "%s: command not found\n", cmd[0]);
	return (fail);
}

static int ft_execct(t_ms *ms, int i, int j)
{
	char	**argv;

	argv = ms->cs[i].ct[j].argv;
	if (!argv[0])
		return (0);
	if (!ft_strncmp(argv[0], "exit", 5))
	{
		ft_exit(ms, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "cd", 3))
	{
		ft_cd(ms, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "export", 7))
	{
		ft_export(ms, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "unset", 6))
	{
		ft_unset(ms, argv);
		return (0);
	}
	ms->cs[i].pids[j] = fork();
	if (ms->cs[i].pids[j]  < 0)
		exit(255); //should not happen but needs better handling
	if (ms->cs[i].pids[j] == 0)
	{
		if (!ft_strncmp(argv[0], "pwd", 4))
			ft_pwd(ms, argv);
		else if (!ft_strncmp(argv[0], "env", 4))
			ft_env(ms, argv);
		else if (!ft_strncmp(argv[0], "echo", 5))
			ft_echo(ms, argv);
		else //execve
		{
			ft_exec(ms, ms->cs[i].ct[j].argv);
			ft_printf_fd(2, "command not found: %s\n", argv[0]);
			ft_free(ms);
			exit(127);
		}
	}
	return (0);
}

static int ft_execcs(t_ms *ms, int i)
{
	int	j;
	int	w;

	j = 0;
	ms->cs[i].pipes = NULL;
	ms->cs[i].pids = NULL;
	if (ms->cs[i].ctn > 1)
	{
		ms->cs[i].pipes = ft_calloc(sizeof(int[2]), ms->cs[i].ctn - 1);
		if (!ms->cs[i].pipes)
			return (1);
	}
	if (ms->cs[i].ctn)
	{
		ms->cs[i].pids = ft_calloc(sizeof(int), ms->cs[i].ctn);
		if (!ms->cs[i].pids)
			return (1);
	}
	while (j < ms->cs[i].ctn)
	{
		if (ft_execct(ms, i, j))
			return (1);
		j++;
	}
	w = 0;
	while (w < ms->cs[i].ctn)
	{
		if (ms->cs[i].pids[w])
			waitpid(ms->cs[i].pids[w] , NULL, 0);
		w++;
	}
	return (0);
}

int	ft_executor(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < ms->csn)
	{
		if (ft_execcs(ms, i))
			return (1);
		i++;
	}
	return (0);
}