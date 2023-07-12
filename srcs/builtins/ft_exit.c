/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:11:51 by okraus            #+#    #+#             */
/*   Updated: 2023/07/12 17:25:01 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// need check for too many arguments and to be passed as an argument

void	ft_exit(t_ms *ms)
{
	ft_free(ms);
	if ((ms->s + 4))
		ms->exit = ft_atoi((ms->s + 4)) % 256;
	ms->live = 0;
}
