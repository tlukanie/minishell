/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:07:18 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/16 13:25:53 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_wild_fits(char *w, char *s)
{
	int	i;
	int	j;
	int	stopi;
	int	stopj;

	i = 0;
	j = 0;
	if (s && w)
	{
		while (s[i] != '*')
		{
			if (s[i] != w[j])
				return (0);
			i++;
			j++;
		}
	}
	while (s && w && s[i] && w[j])
	{
		while (s[i] == '*')
			i++;
		stopi = i;
		stopj = j;
		while (w[j] && w[j] == s[i])
		{
			i++;
			j++;
		}
		if ((s[i] != '*' && s[i]) || (w[j] && s[i] != '*'))
		{
			i = stopi;
			j = stopj + 1;
		}
	}
	while (s[i] == '*')
		i++;
	if ((!s[i] && s[i - 1] != '*' && !w[j]) || (!s[i] && s[i - 1] == '*'))
		return (1);
	return (0);
}

static void	ft_replace_token_helper(t_list *lst, t_token *token, int mode)
{
	if (mode == 1)
	{
		lst->next = NULL;
		free(token->text);
		token->text = NULL;
		token->type = SPACETOKEN;
	}
	else
	{
		token->type = SPACETOKEN;
		token->text = NULL;
	}
}

void	ft_replace_token(t_ms *ms, t_list *lst, t_token *token, t_list *dir)
{
	t_list	*next;
	t_list	*new;

	next = lst->next;
	ft_replace_token_helper(lst, token, 1);
	while (dir)
	{
		token = malloc(sizeof(t_token));
		if (!token)
			ft_exit(ms, 1);
		token->type = NOQUOTE;
		token->text = ft_stringcopy((char *)dir->content);
		new = ft_lstnew(token);
		if (!new)
			ft_exit(ms, 1);
		ft_lstadd_back(&lst, new);
		token = malloc(sizeof(t_token));
		if (!token)
			ft_exit(ms, 1);
		ft_replace_token_helper(lst, token, 2);
		new = ft_lstnew(token);
		if (!new)
			ft_exit(ms, 1);
		ft_lstadd_back(&lst, new);
		dir = dir->next;
	}
	ft_lstadd_back(&lst, next);
}
