/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:08:16 by okraus            #+#    #+#             */
/*   Updated: 2023/08/13 20:41:40 by tlukanie         ###   ########.fr       */
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
		g_signal = 0;
}
