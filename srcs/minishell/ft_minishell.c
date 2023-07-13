/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:01:49 by okraus            #+#    #+#             */
/*   Updated: 2023/07/13 18:45:42 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// should call actual functions and give them arguments

void	ft_analyse(t_ms *ms)
{
	if (!ft_strncmp(ms->s, "pwd", 4))
	{
		ft_pwd();
	}
	if (!ft_strncmp(ms->s, "exit", 4))
	{
		ft_exit(ms);
	}
	if (!ft_strncmp(ms->s, "env", 3))
	{
		ft_env(ms);
	}
}

int	minishell(t_ms *ms)
{
	while (ms->live)
	{
		ms->s = readline(ms->prompt);
		add_history (ms->s);
		ft_printf("string in loop was: <<\"%s\">>\n", ms->s);
		ft_analyse(ms);
		free(ms->s);
	}
	return (ms->exit);
}

int	main(int argc, char *argv[], char *env[])
{
	t_ms	ms;

	ms.ac = argc;
	ms.av = argv;
	ms.ev = env;
	ft_init(&ms);
	return (minishell(&ms));
}
