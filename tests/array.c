/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01-readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:56:42 by okraus            #+#    #+#             */
/*   Updated: 2023/07/08 11:01:09 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int		(*pipes)[2];
	
	pipes = malloc(sizeof(int[2]) * 10);
	pipes[10][1] = 7;
	printf("%i", pipes[10][1]);
	return (0);
}
