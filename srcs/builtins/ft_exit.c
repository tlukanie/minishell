/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:11:51 by okraus            #+#    #+#             */
/*   Updated: 2023/08/09 14:59:25 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// need check for too many arguments and to be passed as an argument yep

void	ft_exit_builtin(t_ms *ms, char *argv[])
{
	if (argv[1])
		ms->exit = ft_atoi(argv[1]) % 256;
	ms->live = 0;
	ft_free_split(&argv);
	ft_free(ms);
}
