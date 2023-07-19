/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/07/19 19:29:27 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_check_var(t_list *el, char *v)
{
	t_list	*lst;
	t_ev	*ev;

	lst = el;
	while (lst)
	{
		ev = lst->content;
		if (!ft_strncmp(ev->var, v, 1024))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_export(t_ms *ms, char *argv[])
{
	int		r;
	int		i;
	t_ev	*ev;
	t_list	*lst;

	r = 0;
	i = 1;
	while (argv[i] && !r)
	{
		if (ft_strchr(argv[i], '='))
		{
			ev = ft_evinit(argv[i]);
			lst = ft_check_var(ms->el, ev->var);
			if (lst)
			{
				ft_free_ev(lst->content);
				lst->content = ev;
			}
			else
			{
				lst = ft_lstnew(ev);
				if (!ev || !lst)
					r = 1; //needs proper freeing of everyrhing
				ft_lstadd_back(&ms->el, lst);
				ft_sortenv(ms->el);
			}
		}
		else
			r = 127; //change to actual code of not provoding env var;
		i++;
	}
	ft_free_split(&argv);
	ms->err[0] = r;
	ms->err[1] = 1;
}

// void	ft_export(t_ms *ms, char *argv[])
// {
// 	int		r;
// 	int		i;

// 	r = 0;
// 	i = 1;
// 	while (argv[i] && !r)
// 	{
// 		if (ft_strchr(argv[i], '='))
// 		{
// 			r = ft_split_add(&ms->ev, argv[i], ft_splitlen(ms->ev));
// 		}
// 		else
// 			r = 127; //change to actual code of not provoding env var;
// 		i++;
// 	}
// 	ft_free_split(&argv);
// 	ms->err[0] = r;
// 	ms->err[1] = 1;
// }
// should export only the first argument
// should check if the var is legal name
// if the var exists, it overwrites the value
// generate ev structure and add it to the list pr replace existing one.
// check for valid var name
