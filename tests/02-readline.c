/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02-readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:56:42 by okraus            #+#    #+#             */
/*   Updated: 2023/07/08 11:09:41 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char	prompt[] = "\033[35mMini\033[0m\033[37m$\033[0m\033[31mhell\033[0m prompt>";

	char	*s;

	s = readline(prompt);
	printf("string1 was: <<\"%s\">>\n", s);
	printf("end with string starting with '+'\n");
	while (s[0] != '+')
	{
		s = readline(prompt);
		printf("string in loop was: <<\"%s\">>\n", s);
	}
	return (0);
}