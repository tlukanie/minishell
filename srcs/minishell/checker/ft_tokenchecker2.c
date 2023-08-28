/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenchecker2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:54:49 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/28 18:38:01 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_check_text(t_check *check)
{
	if (check->token->type & TEXT && !check->text
		&& (check->stuff == 2 || check->stuff == 1 || check->stuff == 0)
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
	int	helper;

	helper = 0;
	stuff = 0x37FF & ~TEXT;
	if (check->token->type & stuff)
	{
		check->text = 0;
		if (check->stuff == 1)
			check->status = 4;
		else if (check->token->type & REDIRECTS && check->stuff == 2)
			check->status = 1;
		else if (check->stuff == 2)
			check->status = 4;
		else if (check->token->type & ~REDIRECTS)
		{
			check->stuff = 2;
			helper = 1;
			check->status = 1;
		}
		else
			check->status = 1;
		if (!helper)
			check->stuff = 1;
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
		else if (check->token->type & REDIRECTS)
			check->stuff++;
		else if (check->token->type & TEXT)
			check->text++;
		lst = lst->next;
	}
	ft_extra_check_test(check);
}
