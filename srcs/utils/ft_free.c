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
	if(ev->vals)
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
		//ft_printf("ft_free_ct 01\n");
		if (ms->cs[i].ct[j].argv)
			ft_free_split(&ms->cs[i].ct[j].argv);
		//ft_printf("ft_free_ct 02\n");
		//if (ms->cs[i].ct[j].hd)
		//	free(ms->cs[i].ct[j].hd);
		j++;
	}
	//ft_printf("ft_free_ct 03\n");
	free(ms->cs[i].ct);
	ms->cs[i].ct = NULL;
}

void	ft_free_cs(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < ms->csn)
	{
		//ft_printf("ft_free_cs 01\n");
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
	//ft_printf("ft_free_cs 02\n");
	free(ms->cs);
	ms->cs = NULL;
}

void	ft_free(t_ms *ms)
{
	//ft_printf("ft_free 00\n");
	free(ms->prompt);
	//ft_printf("ft_free 01\n");
	if (ms->ev)
		ft_free_split(&ms->ev);
	//ft_printf("ft_free 02\n");
	if (ms->el)
		ft_lstclear(&ms->el, ft_free_ev);
	//ft_printf("ft_free 03\n");
	if (ms->lex)
		ft_lstclear(&ms->lex, ft_free_token);
	if (ms->exe)
		ft_lstclear(&ms->exe, ft_free_token);
	//ft_printf("ft_free 04\n");
	if (ms->csn)
		ft_free_cs(ms);
	//ft_printf("ft_free 05\n");
	//write(1, "freeing simulation complete\n", 28);
}

void	ft_mini_free(t_ms *ms)
{
	//ft_printf("ft_free 00\n");
	//ft_printf("ft_free 01\n");
	//ft_printf("ft_free 02\n");
	//ft_printf("ft_free 03\n");
	if (ms->lex)
		ft_lstclear(&ms->lex, ft_free_token);
	ms->lex = NULL;
	if (ms->exe)
		ft_lstclear(&ms->exe, ft_free_token);
	//ft_printf("ft_free 04\n");
	ms->exe = NULL;
	if (ms->csn)
		ft_free_cs(ms);
	ms->csn = 0;
	//ft_printf("ft_free 05\n");
	//write(1, "freeing simulation complete\n", 28);
}

//free list

//free ev structure

void	ft_exit(t_ms *ms, int err)
{
	static t_ms	*stat;

	if (!stat)
		stat = ms;
	else
	{
		ft_free(stat);
		exit(err);
	}
}
