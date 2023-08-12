/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:52:36 by okraus            #+#    #+#             */
/*   Updated: 2023/08/11 17:25:44 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_fill_exe_token(t_token *token, unsigned int type, int csi)
{
	token->type = type;
	token->text = NULL;
	token->csi = csi;

}

static int	ft_fill_exe_list(t_ms *ms, int c)
{
	t_list	*exenew;
	t_list	*lex;
	t_token *token;
	t_token *ltoken;
	int		i;

	lex = ms->lex;
	i = 0;
	ms->exe = NULL;
	while (lex)
	{
		ltoken = lex->content;
		token = NULL;
		exenew = NULL;
		if (ltoken->type & PAR || ltoken->type & ANDOR)
		{
			token = malloc(sizeof(t_token));
			if (!token)
				return (1);
			ft_fill_exe_token(token, ltoken->type, 0);
		}
		if (ltoken->type & TEXT && !c)
		{
			token = malloc(sizeof(t_token));
			if (!token)
				return (1);
			ft_fill_exe_token(token, ltoken->type, i);
			c = 1;
			i++;
		}
		if (ltoken->type & ANDOR)
			c = 0;
		if (token)
			exenew = ft_lstnew(token);
		if (exenew)
			ft_lstadd_back(&ms->exe, exenew);
		lex = lex->next;
	}
	return (0);
}

static t_list *ft_skip_parentheses(t_list *ex)
{
	t_token *token;

	token = ex->content;
	while (ex)
	{
		token = ex->content;
		if (token->type & CLOSEPAR)
			break;
		if (token->type & OPENPAR)
			ft_skip_parentheses(ex->next);
		ex = ex->next;
	}
	return (ex->next);
}

static t_list *ft_run_parentheses(t_ms *ms, t_list *ex)
{
	t_token *token;
	int		run;

	run = 1;
	while (ex)
	{
		token = ex->content;
		if (token->type & OPENPAR)
		{
			if (run)
				ex = ft_run_parentheses(ms, ex->next);
			else
				ex = ft_skip_parentheses(ex->next);
			continue ;
		}
		if (token->type & CLOSEPAR)
			break;
		if (token->type & TEXT)
			if (run)
				if (ft_execcs(ms, token->csi))
					return (NULL);
		if (token->type & ANDOR)
		{
			if ((ms->error && token->type & OR)
				|| (!ms->error && token->type & AND))
				run = 1;
			else
				run = 0;
		}
		ex = ex->next;
	}
	return (ex->next);
}

static int	ft_bonus_exe_loop(t_ms *ms)
{
	t_list	*ex;
	t_token *token;
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
			if (run)
				ex = ft_run_parentheses(ms, ex->next);
			else
				ex = ft_skip_parentheses(ex->next);
			continue ;
		}
		if (token->type & TEXT)
			if (run)
				if (ft_execcs(ms, token->csi))
					return (1);
		if (token->type & ANDOR)
		{
			if ((ms->error && token->type & OR)
				|| (!ms->error && token->type & AND))
				run = 1;
			else
				run = 0;
		}
		ex = ex->next;
	}	
	return (0);
}

int	ft_bonus_executor(t_ms *ms)
{
	//int	i;
	int c;

	//i = 0;
	c = 0;
	if (ft_fill_exe_list(ms, c))
		return (1);

	if (ft_bonus_exe_loop(ms))
		return (1);

	/*while (i < ms->csn)
	{
		if (ft_execcs(ms, i))
			return (1);
		i++;
		//ft_printf("%i. command structure executed successfully\n", i);
		//delete ms->exe
	}*/
	return (0);
}
