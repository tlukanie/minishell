/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:33:09 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/14 21:33:14 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_heredoc(t_ms *ms, int i, int j)
{
	if (ms->cs[i].ct[j].hd)
		ft_forking_helper(ms, i, j);
}

int	ft_newin(t_ms *ms, int i, int j)
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

int	ft_newout(t_ms *ms, int i, int j)
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
