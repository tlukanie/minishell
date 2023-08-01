/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:19:08 by okraus            #+#    #+#             */
/*   Updated: 2023/07/19 19:32:26 by okraus           ###   ########.fr       */
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
