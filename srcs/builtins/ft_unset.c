/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/08/13 20:25:06 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstrm(t_ms *ms, t_list *lst)
{
	t_list	*l;

	if (lst == ms->el)
	{
		ms->el = ms->el->next;
		ft_lstdelone(lst, ft_free_ev);
	}
	else
	{
		l = ms->el;
		while (l)
		{
			if (l->next == lst)
			{
				l->next = lst->next;
				ft_lstdelone(lst, ft_free_ev);
			}
			l = l->next;
		}
	}
}

int	ft_envlist_rm(t_ms *ms, t_list *el, char *str)
{
	t_list	*lst;
	t_ev	*ev;

	lst = el;
	while (lst)
	{
		ev = lst->content;
		if (!ft_strncmp(ev->var, str, ft_strlen(str) + 1))
		{
			ft_lstrm(ms, lst);
			return (0);
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_unset(t_ms *ms, char *argv[])
{
	int		r;
	int		i;

	r = 0;
	i = 1;
	if (!argv[1])
	{
		ft_printf_fd(2, "unset: not enought arguments\n");
		r = 1;
	}
	while (argv[i])
	{
		r = ft_envlist_rm(ms, ms->el, argv[i]);
		i++;
	}
	ms->error = r;
}
