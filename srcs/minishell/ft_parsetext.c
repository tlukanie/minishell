/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsetext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:23:16 by okraus            #+#    #+#             */
/*   Updated: 2023/08/15 20:31:27 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_jointext_helper(t_token *token, t_token *ntoken, t_list *lst)
{
	t_list	*nlst;
	char	*str;

	token->type = TEXT;
	str = ft_stringcopy(token->text);
	free(token->text);
	token->text = ft_strjoin(str, ntoken->text);
	free(str);
	if (!token->text)
		return (1);
	nlst = lst->next;
	lst->next = lst->next->next;
	ft_lstdelone(nlst, ft_free_token);
	return (0);
}

int	ft_jointext(t_ms *ms)
{
	t_list	*lst;
	t_token	*token;
	t_token	*ntoken;

	lst = ms->lex;
	while (lst && lst->next)
	{
		token = lst->content;
		ntoken = lst->next->content;
		while ((token->type & TEXT) && (ntoken->type & TEXT))
		{
			if (ft_jointext_helper(token, ntoken, lst))
				return (1);
			if (!lst->next)
				break ;
			ntoken = lst->next->content;
		}
		lst = lst->next;
	}
	return (0);
}
