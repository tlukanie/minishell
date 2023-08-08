/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenchecker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:05:49 by okraus            #+#    #+#             */
/*   Updated: 2023/08/08 19:45:01 by okraus           ###   ########.fr       */
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

void	ft_check_parentheses(t_check *check)
{
	if (check->token->type & OPENPAR)
	{
		if (!check->text)
		{
			check->parentheses++;
			if (!check->stuff)
			{
				check->stuff = 1;
				check->status = 1;
			}
		}
		else
			check->status = 3;
	}
	if (check->token->type & CLOSEPAR && check->text)
	{
		if (check->text)
		{
			check->parentheses--;
			if (!check->stuff)
			{
				check->stuff = 1;
				check->status = 1;
			}
		}
		else
			check->status = 3;
	}
	if (check->parentheses < 0)
		check->status = 3;
}

void	ft_check_stuff(t_check *check)
{
	int	stuff;

	stuff = 0x37FF & ~TEXT; //no text and no space
	//ft_printf("token %x, stuff %i\n", check->token->type, check->stuff);
	if (check->token->type & stuff && check->stuff == 1)
	{
		check->text = 0;
		check->stuff = 1;
		check->status = 4;
		//ft_printf("test1\n");
	}
	else if (check->token->type & stuff)
	{
		check->text = 0;
		check->stuff = 1;
		check->status = 1;
		//ft_printf("test2\n");
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
		//ft_printf("token %x, stuff %i text %i, status%i\n",
		//	check->token->type, check->stuff, check->text, check->status);
	}
	ft_extra_check_test(check);
}

int	ft_tokenchecker(t_ms *ms)
{
	t_list	*lst;
	t_check	check_origin;
	t_check	*check;

	check = &check_origin;
	check->text = 0;
	check->parentheses = 0;
	check->stuff = 0;
	check->status = 0;
	lst = ms->lex;
	while (lst)
	{
		check->token = lst->content;
		ft_check_text(check);
		ft_check_parentheses(check);
		ft_check_stuff(check);
		if (check->status > 2)
			break;
		lst = lst->next;
	}
	//ft_printf("status is %i\n", check->status);
	if (!check->stuff)
		return(1);
	
	if (check->parentheses)
	{	if (check->status)
		check->status = 3;
	}
	lst = ms->lex;
	if (!check->status)
		ft_extra_check(lst, check);
	if (check->status)
	{
		ms->error = 2;
		ft_printf_fd(2, "minishell: syntax error, unexpected token\n");
	}
	return (check->status);
}
