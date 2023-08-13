/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/08/13 20:11:01 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_put_export_env(t_list *el)
{
	t_list	*lst;
	t_ev	*ev;

	lst = el;
	while (lst)
	{
		if (lst->content)
		{
			ev = lst->content;
			ft_printf("declare -x %s\n", ev->s);
		}
		lst = lst->next;
	}
}

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

static int	ft_isvalidvar(char *s)
{
	int		i;

	i = 0;
	if (s[i] == '_' || ft_isalpha(s[i]))
	{
		i++;
	}
	else
		return (0);
	while (s[i] == '_' || ft_isalnum(s[i]))
		i++;
	if (s[i] == '=')
		return (1);
	return (0);
}

static void	ft_exportlst_setup(t_ms *ms, t_ev *ev, int r)
{
	t_list	*lst;

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
			r = 1;
		ft_lstadd_back(&ms->el, lst);
		ft_sortenv(ms->el);
	}
}

void	ft_export(t_ms *ms, char *argv[])
{
	int		r;
	int		i;
	t_ev	*ev;

	r = 0;
	i = 1;
	if (!argv[1])
		ft_put_export_env(ms->el);
	while (argv[i])
	{
		if (ft_isvalidvar(argv[i]))
		{
			ev = ft_evinit(argv[i]);
			ft_exportlst_setup(ms, ev, r);
		}
		else
		{
			r = 1;
			ft_printf_fd(2, "minishell: export: '%s': not a \
			valid identifier\n", argv[i]);
		}
		i++;
	}
	ms->err[0] = r;
	ms->err[1] = 1;
	ms->error = 0;
}
