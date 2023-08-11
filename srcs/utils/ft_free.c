/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:19:08 by okraus            #+#    #+#             */
/*   Updated: 2023/08/09 15:03:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(t_ms *ms)
{
	free(ms->prompt);
	ft_free_split(&ms->ev);
	ft_lstclear(&ms->el, ft_free_ev);
	//write(1, "freeing simulation complete\n", 28);
}

//free list

//free ev structure

void	ft_exit(t_ms *ms, int err)
{
	ft_free(ms);
	ms->error = err;
	exit(err);
}
