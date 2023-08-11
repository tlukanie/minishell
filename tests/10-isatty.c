/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-isatty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:54:14 by okraus            #+#    #+#             */
/*   Updated: 2023/07/07 19:19:51 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int fd;

	fd = 0;

	while (fd < 33)
	{
		printf("| fd = %2i, isatty = %i |", fd, isatty(fd));
		fd++;
		if (!(fd % 3))
			printf("\n");
		printf ("use at least one arg\n");
		printf("SUNNY!\n");
	}
	else
	{
		while (argv[i])
		{
			printf("%s\n", argv[i]);
			i++;
		}
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	printf("\n");
	return (0);
}
