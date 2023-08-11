/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_lstat_b-dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:54:14 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 15:37:00 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
//#include <time.h>
//#include <locale.h>
//#include <langinfo.h>
#include <stdio.h>
//#include <stdint.h>


int	main(void)
{
	struct dirent	*dp;
	struct stat     statbuf;
	DIR				*dir;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir() error");
		return 1;
	}
	while ((dp = readdir(dir)) != NULL)
	{
		/* Get entry's information. */
		if (lstat(dp->d_name, &statbuf) == -1)
			continue;
		printf("%s\n", dp->d_name);
	}
	closedir(dir);
	return (0);
}
