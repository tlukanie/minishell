/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:22:53 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 18:25:42 by okraus           ###   ########.fr       */
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

int ft_cd(const char *s)
{
	return(chdir(s));
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	ft_pwd();
	ft_cd(argv[1]);
	ft_pwd();
	return (0);
}