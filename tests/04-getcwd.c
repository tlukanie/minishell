/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:56:42 by okraus            #+#    #+#             */
/*   Updated: 2023/07/08 11:17:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char	prompt[] = "\001\033[35m\002Mini\001\033[0m\033[37m\002$\001\033[0m\033[31m\002hell\001\033[0m\002 prompt>";
	//char	prompt[] = "Mini$hell prompt>";
	char	*s;
	char	cwd[4096];
	char 	*s2;


	s2 = getcwd(cwd, 4096);
	printf("cwd = %s\n", cwd);
	printf("s2  = %s\n", s2);
	printf("cwd = %p\n", cwd);
	printf("s2  = %p\n", s2);
	s = readline(s2);
	add_history (s);
	printf("string1 was: <<\"%s\">>\n", s);
	printf("end with string starting with '+'\n");
	while (s[0] != '+')
	{
		s = readline(prompt);
		add_history (s);
		printf("string in loop was: <<\"%s\">>\n", s);
	}
	return (0);
}
