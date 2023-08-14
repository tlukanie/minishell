/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:58:31 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/14 21:58:37 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_gettoken5(t_token *token, char **strptr)
{
	if (ft_isspace(**strptr))
	{
		ft_getspace(token, strptr);
	}
	else if (**strptr == '\'')
	{
		ft_gettextquote(token, strptr, '\'');
	}
	else if (**strptr == '\"')
	{
		ft_gettextquote(token, strptr, '\"');
	}
	else
	{
		ft_gettext(token, strptr);
	}
}

static void	ft_gettoken4(t_token *token, char **strptr)
{
	if (**strptr == '|' && (*strptr)[1] != '|')
	{
		ft_settoken(token, PIPE, NULL);
		(*strptr)++;
	}
	else if (**strptr == '(')
	{
		ft_settoken(token, OPENPAR, NULL);
		(*strptr)++;
	}
	else if (**strptr == ')')
	{
		ft_settoken(token, CLOSEPAR, NULL);
		(*strptr)++;
	}
	else if (**strptr == '&' && (*strptr)[1] == '&')
	{
		ft_settoken(token, AND, NULL);
		(*strptr)++;
		(*strptr)++;
	}
	else if (**strptr == '|' && (*strptr)[1] == '|')
	{
		ft_settoken(token, OR, NULL);
		(*strptr)++;
		(*strptr)++;
	}
	else
		ft_gettoken5(token, strptr);	
}

static void	ft_gettoken3(t_token *token, char **strptr)
{
	if (**strptr == '2' && (*strptr)[1] == '>' && (*strptr)[2] != '>')
	{
		ft_settoken(token, ERRFILE, NULL);
		(*strptr)++;
		(*strptr)++;
	}
	else if (**strptr == '2' && (*strptr)[1] == '>' && (*strptr)[2] == '>')
	{
		ft_settoken(token, ERRAPPEND, NULL);
		(*strptr)++;
		(*strptr)++;
		(*strptr)++;
	}
	else if (**strptr == '<'  && (*strptr)[1] == '>')
	{
		ft_settoken(token, INOUTFILE, NULL);
		(*strptr)++;
		(*strptr)++;
	}
	else
		ft_gettoken4(token, strptr);	
}

static void	ft_gettoken2(t_token *token, char **strptr)
{
	if (**strptr == '<' && (*strptr)[1] != '<' && (*strptr)[1] != '>')
	{
		ft_settoken(token, INFILE, NULL);
		(*strptr)++;
	}
	else if (**strptr == '>' && (*strptr)[1] != '>')
	{
		ft_settoken(token, OUTFILE, NULL);
		(*strptr)++;
	}
	else if (**strptr == '<' && (*strptr)[1] == '<')
	{
		ft_settoken(token, HEREDOC, NULL);
		(*strptr)++;
		(*strptr)++;
	}
	else if (**strptr == '>'  && (*strptr)[1] == '>')
	{
		ft_settoken(token, APPEND, NULL);
		(*strptr)++;
		(*strptr)++;
	}
	else
		ft_gettoken3(token, strptr);	
}

t_token *ft_gettoken(char **strptr)
{
	t_token	*token;

	while (**strptr)
	{
		token = malloc(sizeof(t_token));
		if (!token)
			return (NULL);
		ft_gettoken2(token, strptr);
		return (token);
	}
	return (NULL);
}
