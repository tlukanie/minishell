/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:08:16 by okraus            #+#    #+#             */
/*   Updated: 2023/08/11 12:44:43 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_wait(t_ms *ms, int pid, int options)
{
	int		err;

	waitpid(pid, &err, options);
	ms->parent--;
	if (WIFEXITED(err))
	{
		ms->error = WEXITSTATUS(err);
	}
	else if (WIFSIGNALED(err))
	{
		if (WTERMSIG(err) == g_signal)
		{
			write(1, "\n", 1);
			g_signal = 0;
		}
		else if (WTERMSIG(err) == SIGQUIT)
			write(1, "\n", 1);
	}
	else
	{
		ms->error = 0;
	}
	if (g_signal)
	{
		//ft_newline(g_signal);
		g_signal = 0;
	}
}