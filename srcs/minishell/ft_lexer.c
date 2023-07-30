/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:16:56 by okraus            #+#    #+#             */
/*   Updated: 2023/07/30 15:40:52 by okraus           ###   ########.fr       */
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
	if (c == '<' || c == '>' || c == '|' || c == ''
		|| c == '\f' || c == '\n')
		return (c);
	return (0);
}

static void ft_settoken(t_token *token, int type, char *s)
{
	token->type = type;
	token->text = s;
}

ft_gettext(token, str)
{
	while (**strptr && !ft_isspace(**strptr) && !ft_istoken(**strptr))
}

static void	ft_gettoken5(t_token *token, char **strptr)
{
	if (ft_isspace(**strptr))
	{
		ft_getspace(token, str); //goes through spaces and generates oen token
	}
	else if (**strptr == '\'')
	{
		ft_gettext(token, str); //single quote
	}
	else if (**strptr == '\"')
	{
		ft_gettext(token, str); // double quote
	}
	else
		ft_gettext(token, str);	
}

static void	ft_gettoken4(t_token *token, char **strptr)
{
	if (**strptr == '|' && *str[1] != '|')
	{
		ft_settoken(token, PIPE, NULL);
		*str++;
	}
	else if (**strptr == '&' && *str[1] == '&')
	{
		ft_settoken(token, AND, NULL);
		*str++;
		*str++;
	}
	else if (**strptr == '|' && *str[1] == '|')
	{
		ft_settoken(token, OR, NULL);
		*str++;
		*str++;
	}
	else
		ft_gettoken5(token, str);	
}

static void	ft_gettoken3(t_token *token, char **strptr)
{
	if (**strptr == '2' && *str[1] == '>' && *str[2] != '>')
	{
		ft_settoken(token, ERRFILE, NULL);
		*str++;
		*str++;
	}
	else if (**strptr == '2' && *str[1] == '>' && *str[2] == '>')
	{
		ft_settoken(token, ERRAPPEND, NULL);
		*str++;
		*str++;
		*str++;
	}
	else if (**strptr == '<'  && *str[1] == '>')
	{
		ft_settoken(token, INOUTFILE, NULL);
		*str++;
		*str++;
	}
	else
		ft_gettoken4(token, str);	
}

static void	ft_gettoken2(t_token *token, char **strptr)
{
	if (**strptr == '<' && *str[1] != '<' && *str[1] != '>')
	{
		ft_settoken(token, INFILE, NULL);
		*str++;
	}
	else if (**strptr == '>' && *str[1] != '>')
	{
		ft_settoken(token, OUTFILE, NULL);
		*str++;
	}
	else if (**strptr == '<' && *str[1] == '<')
	{
		ft_settoken(token, HEREDOC, NULL);
		*str++;
		*str++;
	}
	else if (**strptr == '>'  && *str[1] == '>')
	{
		ft_settoken(token, APPEND, NULL);
		*str++;
		*str++;
	}
	else
		ft_gettoken3(token, str);	
}

t_token *ft_gettoken(char **strptr)
{
	t_token	*token;

	while (**strptr)
	{
		if (ft_isspace(**strptr))
			*str++;
		else
		{
			token = malloc(sizeof(t_token));
			if (!token)
				return (NULL);
			ft_gettoken2(token, str);
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

	token = ft_gettoken(str);
	if (!token)
		return (NULL);
	head = ft_lstnew(token);
	if (!head)
		return (NULL);
	token = ft_gettoken(str);
	while (token)
	{
		node = ft_lstnew(token);
		if (!node)
			return (NULL);
		ft_lstadd_back(&head, node);
		token = ft_gettoken(str);
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
