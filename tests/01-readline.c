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
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char	prompt[] = "Mini$hell prompt>";
	char	*s;

	s = readline(prompt);
	printf("string1 was: %s\n", s);
	printf("end with string starting with '+'\n");
	while (s[0] != '+')
	{
		s = readline(prompt);
		printf("string in loop was: %s\n", s);
	}
	return (0);
}