/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:01:49 by okraus            #+#    #+#             */
/*   Updated: 2023/07/31 17:51:50 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_errorcheck(t_ms *ms)
{
	if (ms->err[1])
		ms->err[1] = 0; //says if internal error should be used
	else if (ms->err[0])
		ms->err[0] = 0; //resets internal status to 0;
}

void	ft_printlex(t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = lst->content;
		ft_printf("<%2i> <%s>\n", token->type, token->text);
		lst = lst->next;
	}
}

// should call actual functions and give them arguments
void	ft_analyse(t_ms *ms)
{
	int		pid;
	char	**argv;
	char	*str;

	ms->lex = ft_lexer(ms);
	ft_printlex(ms->lex);
	// expand $
	if (ft_parser(ms))
	{
		ft_printf_fd(2, "Unexpected token or something bad\n");
		//error message
	}
	ft_printlex(ms->lex);
	//

	//need better split from piscine
	//need to handle quotes as well. ""
	//replace with lexer/parser maybe?
	str = ft_expand(ms, ms->s);
	argv = ft_split(str, ' ');
	if (!argv[0])
		return ;
	if (!ft_strncmp(argv[0], "exit", 5))
	{
		ft_exit(ms, argv);
		return ;
	}
	else if (!ft_strncmp(argv[0], "cd", 3))
	{
		ft_cd(ms, argv);
		return ;
	}
	else if (!ft_strncmp(argv[0], "export", 7))
	{
		ft_export(ms, argv);
		return ;
	}
	else if (!ft_strncmp(argv[0], "unset", 6))
	{
		ft_unset(ms, argv);
		return ;
	}
	pid = fork();
	if (pid < 0)
		exit(255); //should not happen but needs better handling
	if (pid == 0)
	{
		if (!ft_strncmp(argv[0], "pwd", 4))
			ft_pwd(ms, argv);
		else if (!ft_strncmp(argv[0], "env", 4))
			ft_env(ms, argv);
		else if (!ft_strncmp(argv[0], "echo", 5))
			ft_echo(ms, argv);
		else //execve
		{
			ft_printf_fd(2, "command not found: %s\n", argv[0]);
			ft_free_split(&argv);
			ft_free(ms);
			exit(127);
		}
	}
	waitpid(pid, NULL, 0);
	ft_free_split(&argv);
}

int	minishell(t_ms *ms)
{
	while (ms->live)
	{
		ms->s = readline(ms->prompt);
		if(!ms->s)
		{
			ft_free(ms);

			break ;
		}
		else
		{
			add_history (ms->s);
			ft_analyse(ms);
			ft_errorcheck(ms);
			free(ms->s);
		}
	}
	write(1, "exit\n", 5);
	return (ms->exit);
}

int	main(int argc, char *argv[], char *env[])
{
	t_ms	ms;

	ms.ac = argc;
	ms.av = argv;
	ms.ev = env;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_newline);
	ft_init(&ms);
	return (minishell(&ms));
}
