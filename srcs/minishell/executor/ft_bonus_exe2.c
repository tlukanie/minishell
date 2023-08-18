/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_exe2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:45:01 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/18 15:27:49 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_list	*ft_skip_parentheses(t_list *ex)
{
	t_token	*token;

	token = ex->content;
	while (ex)
	{
		token = ex->content;
		if (token->type & CLOSEPAR)
			break ;
		if (token->type & OPENPAR)
		{
			ex = ft_skip_parentheses(ex->next);
			continue ;
		}
		ex = ex->next;
	}
	return (ex->next);
}

static int	ft_andor(t_ms *ms, t_token *token)
{
	int	r;

	if ((ms->error && token->type & OR)
		|| (!ms->error && token->type & AND))
		r = 1;
	else
		r = 0;
	return (r);
}

static t_list	*ft_open_par(t_ms *ms, t_list *ex, int run)
{
	if (run)
		ex = ft_run_parentheses(ms, ex->next);
	else
		ex = ft_skip_parentheses(ex->next);
	return (ex);
}

t_list	*ft_run_parentheses(t_ms *ms, t_list *ex)
{
	t_token	*token;
	int		run;

	run = 1;
	while (ex)
	{
		token = ex->content;
		if (token->type & OPENPAR)
		{
			ex = ft_open_par(ms, ex, run);
			continue ;
		}
		if (token->type & CLOSEPAR)
			break ;
		if (token->type & TEXT)
			if (run)
				if (ft_execcs(ms, token->csi))
					return (NULL);
		if (token->type & ANDOR)
		{
			run = ft_andor(ms, token);
		}
		ex = ex->next;
	}
	return (ex->next);
}

int	ft_bonus_exe_loop(t_ms *ms)
{
	t_list	*ex;
	t_token	*token;
	int		run;

	run = 1;
	if (!ms->exe)
		return (1);
	ex = ms->exe;
	while (ex)
	{
		token = ex->content;
		if (token->type & OPENPAR)
		{
			ex = ft_open_par(ms, ex, run);
			continue ;
		}
		if (token->type & TEXT)
			if (run)
				if (ft_execcs(ms, token->csi))
					return (1);
		if (token->type & ANDOR)
			run = ft_andor(ms, token);
		ex = ex->next;
	}
	return (0);
}
