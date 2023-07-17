/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/07/17 14:55:37 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export(t_ms *ms, char *argv[])
{
	int		r;
	int		i;

	r = 0;
	i = 1;
	while (argv[i] && !r)
	{
		if (ft_strchr(argv[i], '='))
		{
			r = ft_split_add(&ms->ev, argv[i], ft_splitlen(ms->ev));
		}
		else
			r = 127; //change to actual code of not provoding env var;
		i++;
	}
	ft_free_split(argv);
	ms->err[0] = r;
	ms->err[1] = 1;
}
// should export only the first argument
// should check if the var is legal name
// if the var exists, it overwrites the value