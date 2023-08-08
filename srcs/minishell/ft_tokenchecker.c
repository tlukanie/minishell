/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenchecker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:05:49 by okraus            #+#    #+#             */
/*   Updated: 2023/08/08 19:04:05 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_checker
{
	t_token	*token;
	int		text;
	int		stuff; //no space and no text;
	int		parentheses;
	int		space;
	int		status;
}	t_check;

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
	{
		check->status = 3;
	}
	if (check->status)
	{
		ms->error = 2;
		ft_printf_fd(2, "minishell: syntax error, unexpected token\n");
	}
	return (check->status);
}
