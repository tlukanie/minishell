/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 11:17:01 by okraus            #+#    #+#             */
/*   Updated: 2023/07/30 17:56:12 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_getvar(char *s)
{
	int		i;
	char	*var;

	i = 0;
	if (s[i] == '_' || ft_isalpha(s[i]))
	{
		i++;
	}
	else
		return (NULL);
	while (s[i] == '_' || ft_isalnum(s[i]))
		i++;
	var = ft_calloc(sizeof(char), (i + 2));
	ft_strlcpy(var, s, i + 1);
	return (var);
}

static int	ft_getvarlen(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '_' || ft_isalpha(s[i]))
	{
		i++;
	}
	else
		return (-1);
	while (s[i] == '_' || ft_isalnum(s[i]))
		i++;
	return (i);	
}

static char	*ft_replacevar(t_ms *ms, char *s, int *i)
{
	char	*strstart;
	char	*strend;
	char	*var;
	char	*val;
	int		j;


	j = ft_getvarlen(&s[(*i) + 1]);
	var = ft_getvar(&s[(*i) + 1]);
	val = ft_getenvval(ms, var);
	ft_printf("j = %i\n", j);
	if (j < 0)
		strend = ft_stringcopy((&s[(*i)]));
	else
		strend = ft_stringcopy((&s[(*i) + j + 1]));
	s[*i] = 0;
	strstart = ft_stringcopy((s));
	ft_printf("start= %s\n", strstart);
	ft_printf("val= %s\n", val);
	ft_printf("end= %s\n", strend);
	s = ft_strjoin(strstart, val);
	s = ft_strjoin_freeleft(s, strend);
	ft_printf("s = %s\n", s);
	ft_printf("*i = %i, s = %s\n", *i, &s[(*i)]);
	if (val)
		*i += ft_strlen(val) - 1;
	ft_printf("*i = %i, s = %s\n", *i, &s[(*i)]);
	return (s);
}

char	*ft_expand(t_ms *ms, char *s)
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
