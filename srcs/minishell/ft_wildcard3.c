/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:35:00 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/16 13:35:02 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_compare(char *s, t_list **dir)
{
	t_list	*lst;
	t_list	*plst;
	char	*w;

	lst = *dir;
	plst = NULL;
	while (lst)
	{
		w = lst->content;
		if (!ft_wild_fits(w, s))
		{
			if (plst)
			{
				plst->next = lst->next;
				ft_lstdelone(lst, ft_delstring);
				lst = plst->next;
			}
			else
			{
				*dir = lst->next;
				ft_lstdelone(lst, ft_delstring);
				lst = *dir;
			}
		}
		else
		{
			plst = lst;
			lst = lst->next;
		}
	}
}

static void	ft_replace_wild(t_ms *ms, t_list *lst, t_token *token, char *s)
{
	t_list	*dir;

	if (s && s[0] != '.')
		dir = ft_get_dir(0);
	else
		dir = ft_get_dir(1);
	ft_compare(s, &dir);
	if (dir)
		ft_replace_token(ms, lst, token, dir);
	ft_lstclear(&dir, ft_delstring);
}

void	ft_expand_wild(t_ms *ms, t_list *lst)
{
	int		i;
	char	*s;
	t_token	*token;

	(void)ms;
	token = lst->content;
	if (token->type == NOQUOTE)
	{
		i = 0;
		s = token->text;
		while (s && s[i])
		{
			if (s[i] == '*')
			{
				ft_replace_wild(ms, lst, token, s);
				break ;
			}
			i++;
		}
	}
}
