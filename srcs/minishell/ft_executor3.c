/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:16:12 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/14 14:16:16 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_closepipes(t_ms *ms, int i)
{
	int k;

	k = 0;
	if (ms->cs[i].ctn > 1)
	{
		while (k < ms->cs[i].ctn - 1)
		{
			close(ms->cs[i].pipes[k][0]);
			close(ms->cs[i].pipes[k][1]);
			k++;
		}
	}
	k = 0;
	while (k < ms->cs[i].ctn)
	{
		if (ms->cs[i].ct[k].hd)
		{
			if (ms->cs[i].ct[k].hdpipe[0] > 2)
				close(ms->cs[i].ct[k].hdpipe[0]);
			if (ms->cs[i].ct[k].hdpipe[1] > 2)
				close(ms->cs[i].ct[k].hdpipe[1]);
		}
		k++;
	}
}

void	ft_closefds(t_ms *ms, int i)
{
	int k;

	k = 0;
	while (k < ms->cs[i].ctn)
	{
		if (ms->cs[i].ct[k].fds[0][0] > 2)
			if (close (ms->cs[i].ct[k].fds[0][0]))
				printf("Error closing input %i\n", ms->cs[i].ct[k].fds[0][0]);
		if (ms->cs[i].ct[k].fds[1][0] > 2)
			if (close (ms->cs[i].ct[k].fds[1][0]))
				printf("Error closing output %i\n", ms->cs[i].ct[k].fds[1][0]);
		if (ms->cs[i].ct[k].fds[2][0] > 2)
			if (close (ms->cs[i].ct[k].fds[2][0]))
				printf("Error closing err %i\n", ms->cs[i].ct[k].fds[2][0]);
		k++;
	}
}

int ft_execct(t_ms *ms, int i, int j)
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
		ft_closepipes(ms, i);
		ft_closefds(ms, i);
		if (!ft_strncmp(argv[0], "pwd", 4))
			ft_pwd(ms, argv);
		else if (!ft_strncmp(argv[0], "env", 4))
			ft_env(ms, argv);
		else if (!ft_strncmp(argv[0], "echo", 5))
			ft_echo(ms, argv);
		else
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			ft_exec(ms, ms->cs[i].ct[j].argv);
			ft_exit(NULL, 127);
		}
	}
	else
		signal(SIGINT, ft_global_sig);
	return (0);
}