/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenchecker2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:54:49 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/15 19:21:17 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_text(t_check *check)
{
	if (check->token->type & TEXT && !check->text
		&& (check->stuff == 1 || check->stuff == 0)
		&& (check->status == 1 || check->status == 0))
	{
		check->text = 1;
		check->stuff = -1;
		check->status = 0;
	}
}

void	ft_check_stuff(t_check *check)
{
	int	stuff;

	stuff = 0x37FF & ~TEXT;
	if (check->token->type & stuff && check->stuff == 1)
	{
		check->text = 0;
		check->stuff = 1;
		check->status = 4;
	}
	else if (check->token->type & stuff)
	{
		check->text = 0;
		check->stuff = 1;
		check->status = 1;
	}
}

void	ft_extra_check_test(t_check *check)
{
	if (check->text <= check->stuff)
		check->status = 5;
	check->text = 0;
	check->stuff = 0;
}

void	ft_extra_check(t_list *lst, t_check *check)
{
	check->text = 0;
	check->stuff = 0;
	while (lst && !check->status)
	{
		check->token = lst->content;
		if (check->token->type & PIPE || check->token->type & ANDOR)
			ft_extra_check_test(check);
		if (check->token->type & REDIRECTS)
			check->stuff++;
		if (check->token->type & TEXT)
			check->text++;
		lst = lst->next;
	}
	ft_extra_check_test(check);
}
