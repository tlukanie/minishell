/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_lstat_a-file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:43:03 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 15:35:37 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
#include <bsd/string.h> //strmode -lbsd for compilation
#include <stdlib.h> //calloc;

int	main(void)
{
	

	struct stat buffer;
	int         status;
	struct passwd  *pwd;
	struct group   *grp;
	struct tm      *tm;
	char            datestring[256];
	char			*bp;

	status = lstat("softlink.c", &buffer);

	/* Print out type, permissions, and number of links. */
	// sperm function does not exist, strmode it is
	bp = calloc(12, 1);
	strmode(buffer.st_mode, bp);
	printf("%10.10s", bp);
	printf("%4lu", buffer.st_nlink);
	/* Print out owner's name if it is found using getpwuid(). */
	if ((pwd = getpwuid(buffer.st_uid)) != NULL)
		printf(" %-8.8s", pwd->pw_name);
	else
		printf(" %-8d", buffer.st_uid);
	/* Print out group name if it is found using getgrgid(). */
	if ((grp = getgrgid(buffer.st_gid)) != NULL)
		printf(" %-8.8s", grp->gr_name);
	else
		printf(" %-8d", buffer.st_gid);
	/* Print size of file. */
	printf(" %9jd", (intmax_t)buffer.st_size);
	tm = localtime(&buffer.st_mtime);
	/* Get localized date string. */
	strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
	printf(" %s \n", datestring);
	free(bp);
	return (0);
}
