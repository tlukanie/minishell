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
#include <curses.h>
#include <term.h>
#include <stdlib.h>

int	main(void)
{
	const char	*name;
	char		*term;
	int			height;
	int			width;

	name = "TERM";
	if ((term = getenv(name)) == NULL)
		return (1);
	printf("My terminal is %s.\n", term);
	//buffer is ignored by emulation layer, so NULL (but leaks)
	tgetent(NULL, term);
	height = tgetnum ("li");
	width = tgetnum ("co");
	printf("H : %d\nL : %d\n", height, width);
	return (0);
}