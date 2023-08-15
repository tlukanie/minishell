/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:32:30 by okraus            #+#    #+#             */
/*   Updated: 2023/08/14 18:58:13 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_fillct(t_ct *ct, char *text, int *r)
{
	if (!(*r))
	{
		if (!ct->argv && text)
		{
			ct->argv = malloc(sizeof(char *) * 2);
			if(!ct->argv)
				return (1);
			ct->argv[0] = ft_stringcopy(text);
			if (!ct->argv[0])
				return (1);
			ct->argv[1] = NULL;
		}
		else if (ct->argv && text)
		{
			if (ft_split_add(&ct->argv, text, ft_splitlen(ct->argv)))
			{
				ft_printf("err3\n");
				return (1);
			}
		}
	}
	else
	{
		if (ft_fillctfd(ct, text, r))
			return (2);
	}
	return (0);
}

int	ft_fillcts(t_ms *ms)
{
	t_list			*lst;
	t_token			*token;
	unsigned int	i;
	int				j;
	int				r;

	lst = ms->lex;
	i = 0;
	r = 0;
	j = 0;
	while (lst)
	{
		token = lst->content;
		if (token->type & ANDOR)
		{
			j = 0;
			i++;
			ms->cs[i].ct[j].argv = NULL;
		}
		else if (token->type & PIPE)		
			j++;
		else if (token->type & REDIRECTS)
			r = token->type & REDIRECTS;
		else if (token->type & TEXT)
		{
			if (ft_fillct(&(ms->cs[i].ct[j]), token->text, &r))
			{
				return(1);
			}
		}
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
			j++;	
		}
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
