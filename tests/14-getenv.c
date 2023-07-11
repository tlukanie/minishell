/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14-getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:54:14 by okraus            #+#    #+#             */
/*   Updated: 2023/07/11 16:20:45 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("PATH: %s\n", getenv("PATH"));
	printf("PWD: %s\n", getenv("PWD"));
	printf("OLDPWD: %s\n", getenv("OLDPWD"));
	return (0);
}
