/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-ttyslot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:54:14 by okraus            #+#    #+#             */
/*   Updated: 2023/07/12 14:59:06 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	printf("ttyslot: %i\n", ttyslot());
	return (0);
}