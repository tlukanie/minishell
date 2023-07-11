/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10-isatty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:54:14 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 15:37:01 by okraus           ###   ########.fr       */
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
	}
	printf("\n");
	return (0);
}
