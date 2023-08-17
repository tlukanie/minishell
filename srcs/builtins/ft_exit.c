/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:11:51 by okraus            #+#    #+#             */
/*   Updated: 2023/08/17 14:53:12 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_error_isbignumber(char *s)
{
	if (ft_strlen(s) > 11)
		return (1);
	else
	{
		if (ft_latoi(s) < -2147483648
			|| ft_latoi(s) > 2147483647)
		{
			return (1);
		}
	}
	return (0);
}

static int	ft_check_error_isnumber(char *s)
{
	int	j;

	j = 0;
	if (ft_isdigit(s[j]) || s[j] == '-' || s[j] == '+')
		j++;
	while (ft_isdigit(s[j]))
		j++;
	if (s[j])
	{
		return (1);
	}
	if (!ft_isdigit(s[j - 1]))
	{
		return (1);
	}
	return (0);
}

static int	ft_check_exit_arg(char *str)
{
	if (!str)
		return (0);
	if (!str[0])
		return (1);
	if (ft_check_error_isnumber(str))
		return (1);
	if (ft_check_error_isbignumber(str))
		return (1);
	return (0);
}

void	ft_exit_builtin(t_ms *ms, char *argv[])
{
	ms->live = 0;
	if (argv[1])
	{
		ms->exit = ft_atoi(argv[1]) % 256;
		ms->live = 0;
		if (argv[2])
		{
			ms->exit = 0;
			ms->live = 1;
			ms->error = 1;
			ft_printf_fd(2, "minishell: exit: too many arguments\n");
		}
		if (ft_check_exit_arg(argv[1]))
		{
			ms->exit = 2;
			ms->live = 0;
			ms->error = 2;
			ft_printf_fd(2, "minishell: exit: numeric argument required\n");
		}
	}
}
