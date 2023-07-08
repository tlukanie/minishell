/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:56:42 by okraus            #+#    #+#             */
/*   Updated: 2023/07/08 11:17:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#undef _POSIX_SOURCE
#include <stdio.h>

int	main(void)
{
	DIR				*dir;
	struct dirent	*entry;

	if ((dir = opendir(".")) == NULL)
		perror("opendir() error");
	else
	{
		printf("contents of current dir:\n");
		while ((entry = readdir(dir)) != NULL)
			printf("  %s\n", entry->d_name);
		closedir(dir);
	}
}
