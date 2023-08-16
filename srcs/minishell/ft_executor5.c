/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:37:45 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/16 16:19:41 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_print_warning(t_ms *ms, int i, int j)
{
	ft_printf_fd(2, "\nminishell: warning: here-document ");
	ft_printf_fd(2, "delimited by end-of-file (wanted");
	ft_printf_fd(2, "`%s')\n", ms->cs[i].ct[j].hd);
	ft_exit(NULL, 1);
}

static void	ft_exit_helper(t_ms *ms, char *line, int i, int pid)
{
	if (pid < 0)
	{
		ft_exit(NULL, 1);
	}
	else if (line)
	{
		free(line);
		ft_closefds(ms, i);
		ft_closepipes(ms, i);
		ft_exit(NULL, 1);
	}
}

static void	ft_error_creating_pipe(void)
{
	ft_printf_fd(2, "Error with creating pipe\n");
	ft_exit(NULL, 1);
}

static void	ft_while_loop_end(t_ms *ms, int i, int j, char *line)
{
	write(ms->cs[i].ct[j].hdpipe[1], line, ft_strlen(line));
	free(line);
}

void	ft_forking_helper(t_ms *ms, int i, int j)
{
	char	*line;
	int		pid;

	line = NULL;
	if (pipe(ms->cs[i].ct[j].hdpipe) == -1)
		ft_error_creating_pipe();
	pid = fork();
	ft_exit_helper(ms, line, i, pid);
	if (pid == 0)
	{
		signal(SIGINT, ft_newglobal_sig);
		while (1)
		{
			write (1, "> ", 2);
			line = get_next_line(0);
			if (line == NULL)
				ft_print_warning(ms, i, j);
			if (ft_strncmp(line, ms->cs[i].ct[j].hd,
					ft_strlen(ms->cs[i].ct[j].hd)) == 0)
				break ;
			ft_while_loop_end(ms, i, j, line);
		}
		ft_exit_helper(ms, line, i, pid);
	}
	ft_wait(ms, pid, 0);
}
