/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:08:08 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 18:12:51 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
//replace with libft
#include <string.h>

void ft_echo(char *s)
{
	write(1, s, strlen(s));
	write(1, "\n", 1);
}

void ft_echon(char *s)
{
	write(1, s, strlen(s));
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	ft_echo(argv[1]);
	ft_echon(argv[1]);
	return (0);
}
