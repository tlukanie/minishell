/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05-readdir,opendir,closedir.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:56:42 by okraus            #+#    #+#             */
/*   Updated: 2023/07/09 11:41:09 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>

int	main(void)
{
	DIR				*dir;
	struct dirent	*entry;
	const char		*directory = ".";

	if ((dir = opendir(directory)) == NULL)
		perror("opendir() error");
	// maybe add function to store strings and sort them?
	else
	{
		printf("contents of current dir:\n");
		while ((entry = readdir(dir)) != NULL)
			printf("  %s\n", entry->d_name);
		closedir(dir);
	}
	return (0);
}
