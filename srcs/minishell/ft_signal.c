/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:56:38 by okraus            #+#    #+#             */
/*   Updated: 2023/08/11 10:56:56 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_newline(int signal)
{
	if (signal == SIGINT)
	{
		//printf("Process %i is replacing line...\n", getpid());
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
		//printf("Process %i is replacing line...\n", getpid());
		//sleep(1);
	}
}

void	ft_newnewline(int signal)
{
	if (signal == SIGINT)
	{
		//printf("Process %i is replacing newnew line...\n", getpid());
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
		//printf("Process %i is replacing newnew line...\n", getpid());
		//sleep(1);

	}
}

void	ft_global_sig(int signal)
{
	if (signal == SIGINT)
	{
		//printf("Process %i is setting global...\n", getpid());
		write(1, "\n", 1);
		g_signal = SIGINT;
	}
}

void	ft_exit_sig(int signal)
{
	if (signal == SIGINT)
	{
		//printf("Process %i is exiting...\n", getpid());
		exit(130);
	}
}