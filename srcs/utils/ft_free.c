/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:19:08 by okraus            #+#    #+#             */
/*   Updated: 2023/08/13 16:46:39 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_ev(void *ptr)
{
	t_ev	*ev;

	ev = ptr;
	if (ev->s)
		free(ev->s);
	if (ev->var)
		free(ev->var);
	if (ev->vals)
		ft_free_split(&ev->vals);
	free(ev);
	ev = NULL;
}

void	ft_free_token(void *ptr)
{
	t_token	*token;

	token = ptr;
	if (token->text)
	{
		free(token->text);
		token->text = NULL;
	}
	token->text = NULL;
	free(token);
	token = NULL;
}

void	ft_free_ct(t_ms *ms, int i)
{
	int	j;

	j = 0;
	while (j < ms->cs[i].ctn)
	{
		if (ms->cs[i].ct[j].argv)
			ft_free_split(&ms->cs[i].ct[j].argv);
		j++;
	}
	free(ms->cs[i].ct);
	ms->cs[i].ct = NULL;
}

void	ft_free_cs(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < ms->csn)
	{
		if (ms->cs[i].ctn)
		{
			ft_free_ct(ms, i);
			ms->cs[i].ct = NULL;
		}
		if (ms->cs[i].ctn > 1)
		{
			free(ms->cs[i].pipes);
			ms->cs[i].pipes = NULL;
		}
		free(ms->cs[i].pids);
		ms->cs[i].pids = NULL;
		i++;
	}
	free(ms->cs);
	ms->cs = NULL;
}

void	ft_free(t_ms *ms)
{
	free(ms->prompt);
	if (ms->ev)
		ft_free_split(&ms->ev);
	if (ms->el)
		ft_lstclear(&ms->el, ft_free_ev);
	if (ms->lex)
		ft_lstclear(&ms->lex, ft_free_token);
	if (ms->exe)
		ft_lstclear(&ms->exe, ft_free_token);
	if (ms->csn)
		ft_free_cs(ms);
}
