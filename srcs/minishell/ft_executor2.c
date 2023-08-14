/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:48:42 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/14 14:15:58 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_open_pipes(t_ms *ms, int i)
{
	int	j;

	j = 0;
	ms->cs[i].pipes = ft_calloc (sizeof (int [2]), ms->cs[i].ctn - 1);
	if (!ms->cs[i].pipes)
		return (1);
	while (j < ms->cs[i].ctn - 1)
	{
		if (pipe(ms->cs[i].pipes[j]) == -1)
		{
			ft_printf_fd(2, "Error with creating pipe\n");
			return (1);
		}
		j++;
	}
	return (0);
}

static void	ft_execcs_wait(t_ms *ms, int i)
{
	int	w;

	w = 0;
	while (w < ms->cs[i].ctn)
	{
		if (ms->cs[i].pids[w])
			ft_wait(ms, ms->cs[i].pids[w], 0);
		w++;
	}
}

static void	ft_execcs_general(t_ms *ms, int i)
{
	ft_closepipes(ms, i);
	ft_execcs_wait(ms, i);
	free(ms->cs[i].pids);
	ms->cs[i].pids = NULL;
	ft_closefds(ms, i);
}

int	ft_execcs(t_ms *ms, int i)
{
	int	j;

	j = 0;
	ms->cs[i].pipes = NULL;
	ms->cs[i].pids = NULL;
	if (ms->cs[i].ctn > 1)
	{
		if (ft_open_pipes(ms, i))
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
	ft_execcs_general(ms, i);
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
