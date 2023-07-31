/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:32:30 by okraus            #+#    #+#             */
/*   Updated: 2023/07/31 19:32:54 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_expand_tilda(t_ms *ms, char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '$')
			s = ft_replacevar(ms, s, &i);
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
				token->text = ft_expandtilda(ms, str);
				if (token->text != str && str)
					free(str);
				if (!token->text)
					return (1);
			}
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

	return (0);
}
