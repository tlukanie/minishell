/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:52:36 by okraus            #+#    #+#             */
/*   Updated: 2023/08/18 15:27:52 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_fill_exe_token(t_token *token, unsigned int type, int csi)
{
	token->type = type;
	token->text = NULL;
	token->csi = csi;
}

static void	ft_create_token_node(t_ms *ms, t_token *token)
{
	t_list	*exenew;

	exenew = NULL;
	if (token)
		exenew = ft_lstnew(token);
	if (exenew)
		ft_lstadd_back(&ms->exe, exenew);
}

static int	ft_fill_exe_list2(t_ms *ms, int *c, t_token *ltoken, int *i)
{
	t_token	*token;

	token = NULL;
	if (ltoken->type & PAR || ltoken->type & ANDOR)
	{
		token = malloc(sizeof(t_token));
		if (!token)
			return (1);
		ft_fill_exe_token(token, ltoken->type, 0);
	}
	if (ltoken->type & TEXT && !*c)
	{
		token = malloc(sizeof(t_token));
		if (!token)
			return (1);
		ft_fill_exe_token(token, ltoken->type, *i);
		*c = 1;
		*i = *i + 1;
	}
	if (ltoken->type & ANDOR)
		*c = 0;
	ft_create_token_node(ms, token);
	return (0);
}

static int	ft_fill_exe_list(t_ms *ms, int c)
{
	t_list	*lex;
	t_token	*ltoken;
	int		i;

	lex = ms->lex;
	i = 0;
	ms->exe = NULL;
	c = 0; 
	while (lex)
	{
		ltoken = lex->content;
		if (ft_fill_exe_list2(ms, &c, ltoken, &i))
			return (1);
		lex = lex->next;
	}
	return (0);
}

int	ft_bonus_executor(t_ms *ms)
{
	int	c;

	c = 0;
	if (ft_fill_exe_list(ms, c))
		return (1);
	if (ft_bonus_exe_loop(ms))
		return (1);
	return (0);
}
