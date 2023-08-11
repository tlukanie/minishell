/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15-tgetent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:42:51 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 16:58:37 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile with -lncurses

#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>

int	main(void)
{
	int			piper[2];
	int			i;

	i = 0;
	while (i < 2048)
	{
		if (pipe(piper) < 0)
			break;
		printf("piper[0] = %i, piper[1] = %i\n", piper[0], piper[1]);
		if (i > 10 && i % 2)
		{
			close(i / 2);
			printf("closeing fd = %i\n", i / 2);
			close(i / 2 + 1);
			printf("closeing fd = %i\n", i / 2 + 1);
			close(i / 2 + 2);
			printf("closeing fd = %i\n", i / 2 + 2);
		}
		i++;
	}
	printf("i = %i\n", i);
	return (0);
}
