/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:32:30 by okraus            #+#    #+#             */
/*   Updated: 2023/08/01 16:29:25 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_replacetilda(t_ms *ms, char *s, int *i)
{
	char	*strstart;
	char	*strend;
	char	*home;

	home = ft_getenvval(ms, "HOME");
	if (home)
		strend = ft_stringcopy((&s[(*i) + 1]));
	else
		return (s);
	s[*i] = 0;
	strstart = ft_stringcopy((s));
	s = ft_strjoin(strstart, home);
	s = ft_strjoin_freeleft(s, strend);
	free(strend);
	free(strstart);
	*i += ft_strlen(home) - 1;
	return (s);
}

static char	*ft_expand_tilda(t_ms *ms, char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '~')
			s = ft_replacetilda(ms, s, &i);
		i++;
	}
	return (s);
}

int	ft_expand_strings(t_ms *ms)
{
	t_list	*lst;
	t_token	*token;
	char	*str;

	lst = ms->lex;
	while (lst)
	{
		token = lst->content;
		str = token->text;
		if (token->type == 0 || token->type == 2)
		{
			if (token->type == 0)
			{
				token->text = ft_expand_tilda(ms, str);
				if (token->text != str && str)
					free(str);
				if (!token->text)
					return (1);
			}
			str = token->text;
			token->text = ft_expand(ms, str);
			if (token->text != str && str)
				free(str);
			if (!token->text)
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_parser(t_ms *ms)
{	
	if (ft_expand_strings(ms))
		return (1);
	// join text tokens
	// expand wildcards
	// create a command structuree

	return (0);
}
