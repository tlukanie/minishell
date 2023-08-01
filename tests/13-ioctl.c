/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13-ioctl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:54:21 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 16:17:30 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define WR_VALUE _IOW('a', 'a', int32_t*)
#define RD_VALUE _IOR('a', 'b', int32_t*)

int	main()
{
	int	fd;
	int	val;
	int	num;

	printf("Opening the Driver\n");
	fd = open("/dev/random", O_RDWR);
	if (fd < 0)
	{
		printf("Unable to open the device file \n");
		return (0);
	}
	printf("Enter the value that you want to send \n");
	scanf("%d", &num);
	printf("Writing the value to the driver \n");
	ioctl(fd, WR_VALUE, (int *)&num);
	sleep(1);
	printf("Reading the value from the driver \n");
	ioctl(fd, RD_VALUE, (int *) &val);
	printf("The value is %d \n", val);

	printf("Closing the driver \n");
	close(fd);
	return (0);
}
