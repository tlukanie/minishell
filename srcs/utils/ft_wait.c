/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:08:16 by okraus            #+#    #+#             */
/*   Updated: 2023/08/09 15:12:19 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_wait(t_ms *ms, int pid, int options)
{
	int		err;

	waitpid(pid, &err, options);
	if (WIFEXITED(err))
	{
		ms->error = WEXITSTATUS(err);
	}
	else
	{
		ms->error = 0;
	}
}