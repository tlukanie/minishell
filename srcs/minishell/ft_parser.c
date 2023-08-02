/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:32:30 by okraus            #+#    #+#             */
/*   Updated: 2023/08/02 19:26:36 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_fillcts(t_ms *ms)
{
	t_list			*lst;
	t_token			*token;
	unsigned int	i;
	int				j;
	int				r;

	lst = ms->lex;
	i = 0;
	while (lst)
	{
		token = lst->content;
		if (token->type & ANDOR)
		{
			j = 0;
			i++;
		}
		else if (token->type & PIPE)		
			j++;
		else if (token->type & REDIRECTS)
			r = 1;
		// the next string after redirect affects fds
		//otherwise add text to argv in cs[i].ct[j];
		//function to fill stuff (maybe r could be static variable in it)
		lst = lst->next;
	}
	return (0);
}

void ft_updatecsn(t_ms *ms)
{
	t_list			*lst;
	t_token			*token;
	unsigned int	i;

	i = 0;
	lst = ms->lex;
	while (lst)
	{
		token = lst->content;
		if (token->type & ANDOR)
			i++;
		token->type |= 0x10000U * i;
		lst = lst->next;
	}
	ms->csn = i + 1;
}

int	ft_createct(t_ms *ms)
{
	t_ct	*ct;
	int		i;

	i = 0;
	while (i < ms->csn)
	{
		ct = malloc(sizeof(t_ct) * (ms->cs[i].ctn));
		if (!ct)
			return (1);
		ms->cs[i].ct = ct;
		i++;
	}
	return (0);
}

void ft_updatectn(t_ms *ms)
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
			ms->cs[i].ctn = j;
			i++;
			j = 0;
		}
		if (token->type & PIPE)
			j++;
		lst = lst->next;
	}
	ms->cs[i].ctn = j;
}

int	ft_createcs(t_ms *ms)
{
	t_cs	*cs;

	cs = malloc(sizeof(t_cs) * (ms->csn));
	if (!cs)
		return (1);
	ms->cs = cs;
	ft_updatectn(ms);
	if (ft_createct(ms))
		return (1);
	return (0);
}

int	ft_parser(t_ms *ms)
{	
	if (ft_expand_strings(ms))
		return (1);
	if (ft_jointext(ms))
		return (2);
	// expand wildcards
	// create binary tree
	// count cs & update token type
	ft_updatecsn(ms);
	// create a command structure
	if (ft_createcs(ms))
		return (5);
	if (ft_fillcts(ms))
		return (6);

	// update paths probably in other function
	return (0);
}
