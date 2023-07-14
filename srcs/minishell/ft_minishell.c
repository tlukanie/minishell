/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:01:49 by okraus            #+#    #+#             */
/*   Updated: 2023/07/14 17:30:53 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_errorcheck(t_ms *ms)
{
	if (ms->err[1])
		ms->err[1] = 0; //says if internal error should be used
	else if (ms->err[0])
		ms->err[0] = 0; //resets internal status to 0;
}

// should call actual functions and give them arguments
void	ft_analyse(t_ms *ms)
{
	int		pid;
	char	**argv;

	argv = ft_split(ms->s, ' '); //need better split from piscine
	if (!argv[0])
		return ;
	if (!ft_strncmp(argv[0], "exit", 5))
	{
		ft_exit(ms, argv);
		return ;
	}
	else if (!ft_strncmp(argv[0], "cd", 3))
	{
		ft_cd(ms, argv);
		return ;
	}
	pid = fork();
	if (pid < 0)
		exit(255); //should not happen but needs better handling
	if (pid == 0)
	{
		if (!ft_strncmp(argv[0], "pwd", 4))
			ft_pwd(ms, argv);
		else if (!ft_strncmp(argv[0], "env", 4))
			ft_env(ms, argv);
		else //execve
		{
			ft_printf_fd(2, "command not found: %s\n", argv[0]);
			ft_free_split(argv);
			ft_free(ms);
			exit(127);
		}
	}
	waitpid(pid, NULL, 0);
}

int	minishell(t_ms *ms)
{
	while (ms->live)
	{
		ms->s = readline(ms->prompt);
		add_history (ms->s);
		ft_analyse(ms);
		ft_errorcheck(ms);
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
