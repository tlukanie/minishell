/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/07/16 13:14:59 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_ms *ms, char *argv[])
{
	int		r;
	int		i;

	r = 0;
	i = 1;
	while (argv[i] && !r)
	{
		if (strchr(argv[i], '='))
		{
			r = 127; //change to actual code of not provoding env var;
		}
		else
		{
			r = ft_split_rm(&ms->ev, ft_findenvvar(ms, argv[i]));
		}
		i++;
	}
	ft_free_split(argv);
	ms->err[0] = r;
	ms->err[1] = 1;
}
