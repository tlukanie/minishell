/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:36:10 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/14 19:36:13 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_sigcall(t_ms *ms, int i, int j)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	ft_exec(ms, ms->cs[i].ct[j].argv);
	ft_exit(NULL, 127);
}

static void	ft_exec_child(t_ms *ms, int i, int j)
{
	char	**argv;

	argv = ms->cs[i].ct[j].argv;
	ft_closepipes(ms, i);
	ft_closefds(ms, i);
	if (!ft_strncmp(argv[0], "pwd", 4))
		ft_pwd(ms, argv);
	else if (!ft_strncmp(argv[0], "env", 4))
		ft_env(ms, argv);
	else if (!ft_strncmp(argv[0], "echo", 5))
		ft_echo(ms, argv);
	else
		ft_sigcall(ms, i, j);
}

static int	ft_check_arg_exit_cd(t_ms *ms, int i, int j)
{
	char	**argv;

	argv = ms->cs[i].ct[j].argv;
	if (ms->cs[i].ct[j].fds[0][0] < 0
		|| ms->cs[i].ct[j].fds[1][0] < 0
		|| ms->cs[i].ct[j].fds[2][0] < 0)
	{
		ms->error = 1;
		return (0);
	}
	if (!argv[0])
		return (0);
	if (!ft_strncmp(argv[0], "exit", 5))
	{
		ft_exit_builtin(ms, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "cd", 3))
	{
		ft_cd(ms, argv);
		return (0);
	}
	else
		return (1);
}

static int	ft_check_arg_export_unset(t_ms *ms, int i, int j)
{
	char	**argv;

	argv = ms->cs[i].ct[j].argv;
	if (!ft_strncmp(argv[0], "export", 7))
	{
		ft_export(ms, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "unset", 6))
	{
		ft_unset(ms, argv);
		return (0);
	}
	else
		return (1);
}

int	ft_execct(t_ms *ms, int i, int j)
{
	if (!ft_check_arg_exit_cd(ms, i, j))
		return (0);
	if (!ft_check_arg_export_unset(ms, i, j))
		return (0);
	ms->cs[i].pids[j] = fork();
	ms->parent++;
	if (ms->cs[i].pids[j] < 0)
		exit(255);
	if (ms->cs[i].pids[j] == 0)
	{
		signal(SIGINT, ft_exit_sig);
		ms->child = 1;
		ft_heredoc(ms, i, j);
		if (ft_dup(ms, i, j))
			return (3);
		ft_exec_child(ms, i, j);
	}
	else
		signal(SIGINT, ft_global_sig);
	return (0);
}
