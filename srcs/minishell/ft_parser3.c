/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:47:22 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/15 17:47:27 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_init_fds(t_ct *ct, int j)
{
	ct[j].fds[0][0] = 0;
	ct[j].fds[0][1] = 0;
	ct[j].fds[1][0] = 1;
	ct[j].fds[1][1] = 0;
	ct[j].fds[2][0] = 2;
	ct[j].fds[2][1] = 0;
	ct[j].hd = NULL;
	ct[j].hdpipe[0] = 0;
	ct[j].hdpipe[1] = 0;
	ct[j].argv = NULL;
}

int	ft_createct(t_ms *ms)
{
	t_ct	*ct;
	int		i;
	int		j;

	i = 0;
	while (i < ms->csn)
	{
		ct = malloc(sizeof(t_ct) * (ms->cs[i].ctn));
		if (!ct)
			return (1);
		j = 0;
		while (j < ms->cs[i].ctn)
		{
			ft_init_fds(ct, j);
			j++;
		}
		ms->cs[i].ct = ct;
		i++;
	}
	return (0);
}

void	ft_updatectn(t_ms *ms)
{
	t_list			*lst;
	t_token			*token;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	lst = ms->lex;
	while (lst)
	{
		token = lst->content;
		if (token->type & ANDOR)
		{
			ms->cs[i].ctn = j + 1;
			i++;
			j = 0;
		}
		if (token->type & PIPE)
			j++;
		lst = lst->next;
	}
	ms->cs[i].ctn = j + 1;
}

int	ft_createcs(t_ms *ms)
{
	t_cs	*cs;
	int		i;

	i = 0;
	cs = malloc(sizeof(t_cs) * (ms->csn));
	if (!cs)
		return (1);
	while (i < ms->csn)
	{
		cs[i].pids = NULL;
		cs[i].pipes = NULL;
		cs[i].ctn = 0;
		i++;
	}
	ms->cs = cs;
	ft_updatectn(ms);
	if (ft_createct(ms))
		return (1);
	return (0);
}

int	ft_parser(t_ms *ms)
{
	ms->csn = 0;
	ms->cs = NULL;
	if (!ms->lex)
		return (0);
	if (ft_expand_strings(ms))
		return (1);
	if (ft_jointext(ms))
		return (2);
	ft_updatecsn(ms);
	if (ft_createcs(ms))
		return (5);
	if (ft_fillcts(ms))
		return (6);
	return (0);
}
