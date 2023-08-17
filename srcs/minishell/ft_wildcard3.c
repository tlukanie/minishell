/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:35:00 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/16 15:32:59 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_compare_helper(t_list **lstptr, t_list **tempptr, t_list **dir)
{
	t_list	*lst;
	t_list	*temp;

	temp = *tempptr;
	lst = *lstptr;
	if (temp)
	{
		temp->next = lst->next;
		ft_lstdelone(lst, ft_delstring);
		lst = temp->next;
	}
	else
	{
		*dir = lst->next;
		ft_lstdelone(lst, ft_delstring);
		lst = *dir;
	}
	*tempptr = temp;
	*lstptr = lst;
}

static void	ft_compare(char *s, t_list **dir)
{
	t_list	*lst;
	t_list	*temp;
	char	*w;

	lst = *dir;
	temp = NULL;
	while (lst)
	{
		w = lst->content;
		if (!ft_wild_fits(w, s))
		{
			ft_compare_helper(&lst, &temp, dir);
		}
		else
		{
			temp = lst;
			lst = lst->next;
		}
	}
}

static void	ft_replace_wild(t_list *lst, t_token *token, char *s)
{
	t_list	*dir;

	if (s && s[0] != '.')
		dir = ft_get_dir(0);
	else
		dir = ft_get_dir(1);
	ft_compare(s, &dir);
	if (dir)
		ft_replace_token(lst, token, dir);
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
				ft_replace_wild(lst, token, s);
				break ;
			}
			i++;
		}
	}
}
