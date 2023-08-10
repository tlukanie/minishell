/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:08:16 by okraus            #+#    #+#             */
/*   Updated: 2023/08/10 19:49:47 by okraus           ###   ########.fr       */
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
		if (WIFSIGNALED(err) == g_signal)
		{
			g_signal = 0;
			//do cool stuuf
		}
	}
	else
	{
		ms->error = 0;
	}
}