/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/07/14 15:34:08 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_ms *ms, char *argv[])
{
	char	cwd[4096];
	char	*s;

	if (argv[1])
	{
		ft_free(ms);
		ft_printf_fd(2, "pwd: too many arguments\n");
		ft_free_split(argv);
		exit(1);
	}
	s = getcwd(cwd, 4096);
	ft_printf("%s\n", s);
	ft_free(ms);
	ft_free_split(argv);
	exit(0);
}
