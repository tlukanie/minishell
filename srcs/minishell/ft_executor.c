/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:11:29 by okraus            #+#    #+#             */
/*   Updated: 2023/08/14 19:08:22 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_exec(t_ms *ms, char **cmd)
{
	int		i;
	int		fail;
	char	*cmdp;
	char	**paths;
	char	**env;

	i = 0;
	fail = 1;
	env = ft_list2split(ms->el);
	if ((ft_strchr(cmd[0], '/')) && access(cmd[0], X_OK) == 0)
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
	ft_free_split(&env);
	return (fail);
}

static int	ft_newin(t_ms *ms, int i, int j)
{
	if (ms->cs[i].ct[j].fds[0][1] == 2)
		return (ms->cs[i].ct[j].hdpipe[0]);
	if (j)
	{
		if (ms->cs[i].ct[j].fds[0][1] == 1)
			return (ms->cs[i].ct[j].fds[0][0]);
		else
			return (ms->cs[i].pipes[j - 1][0]);
	}
	if (ms->cs[i].ct[j].fds[0][1] == 1)
		return (ms->cs[i].ct[j].fds[0][0]);
	return (0);
}

static int	ft_newout(t_ms *ms, int i, int j)
{
	if (j < ms->cs[i].ctn - 1)
	{
		if (ms->cs[i].ct[j].fds[1][1])
			return (ms->cs[i].ct[j].fds[1][0]);
		else
			return (ms->cs[i].pipes[j][1]);
	}
	if (ms->cs[i].ct[j].fds[1][1])
			return (ms->cs[i].ct[j].fds[1][0]);
	return (1);
}

static int	ft_newerr(t_ms *ms, int i, int j)
{
	if (ms->cs[i].ct[j].fds[2][1])
			return (ms->cs[i].ct[j].fds[2][0]);
	return (2);
}

int ft_dup(t_ms *ms, int i, int j)
{
	int newin;
	int newout;
	int newerr;

	newin = ft_newin(ms, i, j);
	newout = ft_newout(ms, i, j);
	newerr = ft_newerr(ms, i, j);
	if (newin > 2)
	{
		if (dup2(newin, STDIN_FILENO) < 0)
		{
			ft_printf_fd(2, "Error duplicating input\n");
			return (1);
		}
	}
	if (newout > 2)
	{
		if (dup2(newout, STDOUT_FILENO) < 0)
		{
			ft_printf_fd(2, "Error duplicating output\n");
			return (2);
		}
	}
	if (newerr > 2)
	{
		if (dup2(newerr, STDERR_FILENO) < 0)
		{
			ft_printf_fd(2, "Error duplicating error output\n");
			return (3);
		}
	}
	return (0);
}

void	ft_heredoc(t_ms *ms, int i, int j)
{
	char	*line;
	int		pid;

	line = NULL;
	if (ms->cs[i].ct[j].hd)
	{
		if (pipe(ms->cs[i].ct[j].hdpipe) == -1)
		{
			ft_printf_fd(2, "Error with creating pipe\n");
			ft_exit(NULL, 1);
		}
		pid = fork();
		if (pid == -1)
			ft_exit(NULL, 1);
		if (pid == 0)
		{
			while (1)
			{
				write (1, "> ", 2);
				line = get_next_line(0);
				if (line == NULL)
				{
					ft_printf_fd(2, "\nminishell: warning: here-document ");
					ft_printf_fd(2, "delimited by end-of-file (wanted");
					ft_printf_fd(2, "`%s')\n", ms->cs[i].ct[j].hd);
					ft_exit(NULL, 1);
				}
				if (ft_strncmp(line, ms->cs[i].ct[j].hd,
					ft_strlen(ms->cs[i].ct[j].hd)) == 0)
					break ;
				write(ms->cs[i].ct[j].hdpipe[1], line, ft_strlen(line));
				free(line);
			}
			free(line);
			ft_closefds(ms, i);
			ft_closepipes(ms, i);
			ft_exit(NULL, 1);
		}
		ft_wait(ms, pid, 0);
	}
}
