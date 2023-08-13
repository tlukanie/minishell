/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:44:29 by okraus            #+#    #+#             */
/*   Updated: 2023/08/13 19:56:17 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_ms *ms, char *argv[])
{
	if (!argv[1])
	{
		ft_putenv(ms->el);
		ft_exit (NULL, 0);
	}
	if (!(access(argv[1], F_OK)))
	{
		ft_printf_fd(2, "env: '%s': Permission denied\n", argv[1]);
		ft_exit(NULL, 126);
	}
	else if (argv[1])
	{
		ft_printf_fd(2, "env: '%s': No such file or directory\n", argv[1]);
		ft_exit(NULL, 127);
	}
	else
	{
		ft_putenv(ms->el);
	}
	ft_exit (NULL, 0);
}
