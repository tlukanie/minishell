/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:11:10 by okraus            #+#    #+#             */
/*   Updated: 2023/07/05 11:40:37 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char *argv[], char *env[])
{
	int	i;

	i = 0;
	if (argc < 2)
	{
		printf ("use at least one arg\n");
		printf("BYE!!!!!!!!\n");
	}
	else
	{
		while (argv[i])
		{
			printf("%s\n", argv[i]);
			i++;
		}
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
