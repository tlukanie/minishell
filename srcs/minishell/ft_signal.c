/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:56:38 by okraus            #+#    #+#             */
/*   Updated: 2023/08/15 18:48:13 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_newline(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	ft_global_sig(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
	}
}

void	ft_newglobal_sig(int signal)
{
	write(1, "\n", 1);
	if (signal == SIGINT)
		exit(130);
}

void	ft_exit_sig(int signal)
{
	if (signal == SIGINT)
		exit(130);
}
