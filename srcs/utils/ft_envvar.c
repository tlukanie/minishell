/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:54:16 by okraus            #+#    #+#             */
/*   Updated: 2023/07/14 17:12:04 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_changeenvvar(t_ms *ms, char *var, char *val)
{
	int		i;
	int		l;
	char	*s;

	i = 0;
	l = ft_strlen(var);
	while (ms->ev[i])
	{
		if (!ft_strncmp(ms->ev[i], var, l)
			&& ms->ev[i][l] == '=')
		{
			s = ft_strjoin(var, "=");
			s = ft_strjoin_freeleft(s, val);
			free(ms->ev[i]);
			ms->ev[i] = s;
			return ;
		}
		i++;
	}
	//add variable if not found?
}

char	*ft_getenvvar(t_ms *ms, char *var)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(var);
	while (ms->ev[i])
	{
		if (!ft_strncmp(ms->ev[i], var, l)
			&& ms->ev[i][l] == '=' && ms->ev[i][l + 1])
		{
			return (&ms->ev[i][l + 1]);
		}
		i++;
	}
	return (NULL);
}
