/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:16:56 by okraus            #+#    #+#             */
/*   Updated: 2023/07/30 16:25:40 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	*ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v'
		|| c == '\f' || c == '\n')
		return (c);
	return (0);
}

static int	*ft_istoken(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&'
		|| c == '(' || c == ')')
		return (c);
	return (0);
}

static void ft_settoken(t_token *token, int type, char *s)
{
	token->type = type;
	token->text = s;
}

void	ft_gettext(t_token *token, char **strptr)
{
	char	*str;
	int		i;

	i = 0;
	while (*strptr[i] && !ft_isspace(*strptr[i]) && !ft_istoken(*strptr[i]))
		i++;
	str = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(str, *strptr, i);
	while(i)
	{
		*strptr++;
		i--;
	}
	ft_settoken(token, NOQUOTE, str);
}

void	ft_gettextquote(t_token *token, char **strptr, char quote)
{
	char	*str;
	int		i;

	i = 0;
	while (*strptr[i] && *strptr[i] != quote)
		i++;
	str = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(str, *strptr, i);
	while(i)
	{
		*strptr++;
		i--;
	}
	if (quote = '\'')
		ft_settoken(token, SINGLEQUOTE, str);
	if (quote = '\"')
		ft_settoken(token, DOUBLEQUOTE, str);
}

void	ft_getspace(t_token *token, char **strptr)
{
	while (ft_isspace(**strptr))
	{
		*strptr++;
	}
	ft_settoken(token, SPACE, NULL);
}

static void	ft_gettoken5(t_token *token, char **strptr)
{
	if (ft_isspace(**strptr))
	{
		ft_getspace(token, strptr); //goes through spaces and generates oen token
	}
	else if (**strptr == '\'')
	{
		ft_gettextquote(token, strptr, '\''); //single quote
	}
	else if (**strptr == '\"')
	{
		ft_gettextquote(token, strptr, '\"'); // double quote
	}
	else
		ft_gettext(token, strptr);	
}

static void	ft_gettoken4(t_token *token, char **strptr)
{
	if (**strptr == '|' && *strptr[1] != '|')
	{
		ft_settoken(token, PIPE, NULL);
		*strptr++;
	}
	else if (**strptr == '(')
	{
		ft_settoken(token, OPENPAR, NULL);
		*strptr++;
	}
	else if (**strptr == ')')
	{
		ft_settoken(token, CLOSEPAR, NULL);
		*strptr++;
	}
	else if (**strptr == '&' && *strptr[1] == '&')
	{
		ft_settoken(token, AND, NULL);
		*strptr++;
		*strptr++;
	}
	else if (**strptr == '|' && *strptr[1] == '|')
	{
		ft_settoken(token, OR, NULL);
		*strptr++;
		*strptr++;
	}
	else
		ft_gettoken5(token, strptr);	
}

static void	ft_gettoken3(t_token *token, char **strptr)
{
	if (**strptr == '2' && *strptr[1] == '>' && *strptr[2] != '>')
	{
		ft_settoken(token, ERRFILE, NULL);
		*strptr++;
		*strptr++;
	}
	else if (**strptr == '2' && *strptr[1] == '>' && *strptr[2] == '>')
	{
		ft_settoken(token, ERRAPPEND, NULL);
		*strptr++;
		*strptr++;
		*strptr++;
	}
	else if (**strptr == '<'  && *strptr[1] == '>')
	{
		ft_settoken(token, INOUTFILE, NULL);
		*strptr++;
		*strptr++;
	}
	else
		ft_gettoken4(token, strptr);	
}

static void	ft_gettoken2(t_token *token, char **strptr)
{
	if (**strptr == '<' && *strptr[1] != '<' && *strptr[1] != '>')
	{
		ft_settoken(token, INFILE, NULL);
		*strptr++;
	}
	else if (**strptr == '>' && *strptr[1] != '>')
	{
		ft_settoken(token, OUTFILE, NULL);
		*strptr++;
	}
	else if (**strptr == '<' && *strptr[1] == '<')
	{
		ft_settoken(token, HEREDOC, NULL);
		*strptr++;
		*strptr++;
	}
	else if (**strptr == '>'  && *strptr[1] == '>')
	{
		ft_settoken(token, APPEND, NULL);
		*strptr++;
		*strptr++;
	}
	else
		ft_gettoken3(token, strptr);	
}

t_token *ft_gettoken(char **strptr)
{
	t_token	*token;

	while (**strptr)
	{
		if (ft_isspace(**strptr))
			*strptr++;
		else
		{
			token = malloc(sizeof(t_token));
			if (!token)
				return (NULL);
			ft_gettoken2(token, strptr);
			return (token);
		}
	}
	return (NULL);
}

static t_list	*ft_getlst(char **strptr)
{
	t_list	*head;
	t_list	*node;
	t_token *token;

	token = ft_gettoken(strptr);
	if (!token)
		return (NULL);
	head = ft_lstnew(token);
	if (!head)
		return (NULL);
	token = ft_gettoken(strptr);
	while (token)
	{
		node = ft_lstnew(token);
		if (!node)
			return (NULL);
		ft_lstadd_back(&head, node);
		token = ft_gettoken(strptr);
	}
	return (head);
}

t_list	*ft_lexer(t_ms *ms)
{
	t_list	*head;
	char	*str;

	if (!ms->s) 
		return (NULL);
	str = ms->s;
	head = ft_getlst(&str);
	if (!head)
	{
		return (NULL);
	}
	return (head);
}
