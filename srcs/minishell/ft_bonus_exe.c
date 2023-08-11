/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:52:36 by okraus            #+#    #+#             */
/*   Updated: 2023/08/11 13:43:05 by okraus           ###   ########.fr       */
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


int	ft_bonus_executor(t_ms *ms)
{
	int	i;
	int c;

	i = 0;
	c = 0;
	if (ft_fill_exe_list(ms, c))
		return (1);
	while (i < ms->csn)
	{
		if (ft_execcs(ms, i))
			return (1);
		i++;
		//ft_printf("%i. command structure executed successfully\n", i);

		//delete ms->exe
	}
	return (0);
}
