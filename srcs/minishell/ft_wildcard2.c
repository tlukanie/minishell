/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:07:18 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/16 15:18:36 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_wild_fits_helper(char *w, char *s, int *iptr, int *jptr)
{
	int	i;
	int	j;
	int	stopi;
	int	stopj;

	i = *iptr;
	j = *jptr;
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
	*iptr = i;
	*jptr = j;
}

int	ft_wild_fits(char *w, char *s)
{
	int	i;
	int	j;

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
		ft_wild_fits_helper(w, s, &i, &j);
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

static void	ft_replace_token_exit(void *ptr, int mode)
{
	t_token	*token;
	t_list	*new;

	if (mode)
	{
		token = ptr;
		if (!token)
			ft_exit(NULL, 1);
	}
	else
	{
		new = ptr;
		if (!new)
			ft_exit(NULL, 1);
	}
}

void	ft_replace_token(t_list *lst, t_token *token, t_list *dir)
{
	t_list	*next;
	t_list	*new;

	next = lst->next;
	ft_replace_token_helper(lst, token, 1);
	while (dir)
	{
		token = malloc(sizeof(t_token));
		ft_replace_token_exit(token, 1);
		token->type = NOQUOTE;
		token->text = ft_stringcopy((char *)dir->content);
		new = ft_lstnew(token);
		ft_replace_token_exit(new, 0);
		ft_lstadd_back(&lst, new);
		token = malloc(sizeof(t_token));
		ft_replace_token_exit(token, 1);
		ft_replace_token_helper(lst, token, 2);
		new = ft_lstnew(token);
		ft_replace_token_exit(new, 0);
		ft_lstadd_back(&lst, new);
		dir = dir->next;
	}
	ft_lstadd_back(&lst, next);
}
