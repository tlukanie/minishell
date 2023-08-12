/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/08/10 19:08:45 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_unset(t_ms *ms, char *argv[])
// {
// 	int		r;
// 	int		i;

// 	r = 0;
// 	i = 1;
// 	while (argv[i] && !r)
// 	{
// 		if (ft_strchr(argv[i], '='))
// 		{
// 			r = 127; //change to actual code of not provoding env var;
// 		}
// 		else
// 		{
// 			r = ft_split_rm(&ms->ev, ft_findenvvar(ms, argv[i]));
// 		}
// 		i++;
// 	}
// 	ft_free_split(&argv);
// 	ms->err[0] = r;
// 	ms->err[1] = 1;
// } delete

void	ft_free_ev(void *ptr)
{
	t_ev	*ev;

	ev = ptr;
	if (ev->s)
		free(ev->s);
	if (ev->var)
		free(ev->var);
	if(ev->vals)
		ft_free_split(&ev->vals);
	free(ev);
	ev = NULL;
}

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
	// not a bash error handling
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
	ft_free_split(&argv);
	ms->error = r;
}

// remove list entry