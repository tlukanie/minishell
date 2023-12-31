/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/08/13 20:08:02 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_echo2(char *argv[])
{
	int	n;
	int	i;
	int	e;

	n = 0;
	e = 0;
	i = 1;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
	{
		n = 1;
		i++;
	}
	if (argv[i])
	{
		e = ft_printf("%s", argv[i]);
		i++;
	}
	while (argv[i] && e >= 0)
	{
		e = ft_printf(" %s", argv[i]);
		i++;
	}
	if (!n && e >= 0)
		e = write(1, "\n", 1);
	return (e);
}

void	ft_echo(t_ms *ms, char *argv[])
{
	int	e;

	(void)ms;
	e = ft_echo2(argv);
	if (e < 0)
		e = 1;
	else
		e = 0;
	ft_exit(NULL, e);
}
