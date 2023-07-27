/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:44:29 by okraus            #+#    #+#             */
/*   Updated: 2023/07/27 15:21:09 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// need check for too many arguments and to be passed as an argument

void	ft_env(t_ms *ms, char *argv[])
{
	// path in argv[1] exists
	if (argv[1])
	{
		ft_free(ms);
		ft_printf_fd(2, "env: '%s': Permission denied\n", argv[1]);
		ft_free_split(&argv);
		exit (126);
	}
	// path in argv[1] does not exist
	else if (argv[1])
	{
		ft_free(ms);
		ft_printf_fd(2, "env: '%s': No such file or directory\n", argv[1]);
		ft_free_split(&argv);
		exit (127);
	}
	else
	{
		//ft_put_split(ms->ev);
		ft_putenv(ms->el);
		ft_free(ms);
		ft_free_split(&argv);
		//usleep(500);
	}
	exit (0);
}
