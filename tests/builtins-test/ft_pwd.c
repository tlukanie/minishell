/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 18:22:16 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
//replace string with libft
#include <string.h>

void ft_pwd(void)
{
	char	cwd[4096];
	char 	*s;

	s = getcwd(cwd, 4096);
	write(1, s, strlen(s));
	write(1, "\n", 1);
}

int	main(void)
{
	ft_pwd();
	return (0);
}
