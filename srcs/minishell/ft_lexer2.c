/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:51:31 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/14 21:51:34 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v'
		|| c == '\f' || c == '\n')
		return (c);
	return (0);
}

int	ft_istoken(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&'
		|| c == '(' || c == ')')
		return (c);
	return (0);
}

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return (0);
}

void	ft_settoken(t_token *token, int type, char *s)
{
	token->type = type;
	token->text = s;
}

void	ft_gettext(t_token *token, char **strptr)
{
	char	*str;
	int		i;

	i = 0;
	while ((*strptr)[i] && !ft_isspace((*strptr)[i])
		&& !ft_istoken((*strptr)[i]) && !ft_isquote((*strptr)[i]))
	{
		i++;
	}
	str = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(str, *strptr, i + 1);
	while (i)
	{
		(*strptr)++;
		i--;
	}
	ft_settoken(token, NOQUOTE, str);
}
