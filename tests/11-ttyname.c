/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11-ttyname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:54:14 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 15:36:56 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int fd;

	fd = 0;

	while (fd < 10)
	{
		printf("| fd = %2i, ttyname = %s |", fd, ttyname(fd));
		fd++;
		printf("\n");
	}
	printf("\n");
	return (0);
}
