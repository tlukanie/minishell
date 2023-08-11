/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:01:49 by okraus            #+#    #+#             */
/*   Updated: 2023/08/11 17:26:08 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal;

void	ft_errorcheck(t_ms *ms)
{
	if (ms->err[1])
		ms->err[1] = 0; //says if internal error should be used
	else if (ms->err[0])
		ms->err[0] = 0; //resets internal status to 0;
}

void	ft_printct(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	while (i < ms->csn)
	{
		j = 0;
		while (j < ms->cs[i].ctn)
		{
			ft_printf("cs %i of %i, ct %i of %i\n", i + 1, ms->csn, j + 1, ms->cs[i].ctn);
			ft_printf("argv:\n");
			if (ms->cs[i].ct[j].argv)
				ft_put_split(ms->cs[i].ct[j].argv);
			ft_printf("fd[0][0] = %i, fd[0][1] = %i\n", ms->cs[i].ct[j].fds[0][0], ms->cs[i].ct[j].fds[0][1]);
			ft_printf("fd[1][0] = %i, fd[1][1] = %i\n", ms->cs[i].ct[j].fds[1][0], ms->cs[i].ct[j].fds[1][1]);
			ft_printf("fd[2][0] = %i, fd[2][1] = %i\n\n", ms->cs[i].ct[j].fds[2][0], ms->cs[i].ct[j].fds[2][1]);
			j++;
		}
		i++;
	}
}

void	ft_printlex(t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = lst->content;
		ft_printf("<%8x> <%8i> <%s>\n", token->type, token->csi, token->text);
		lst = lst->next;
	}
}

// should call actual functions and give them arguments
void	ft_analyse(t_ms *ms)
{
	ms->lex = ft_lexer(ms);

	// expand $
	//ft_printf("checkpoint A\n");
	if (ft_tokenchecker(ms))
	{
		//ft_printf("Token checker returned %i\n", ft_tokenchecker(ms));
		return ;
	}
	// ft_printf("new lex 4b \n");
	// ft_printlex(ms->lex);
	if (ft_parser(ms))
	{
		ft_printf_fd(2, "Unexpected token or something bad\n");
		//error message
	}
	//ft_printf("Tokens after expansion:\n");
	//ft_printf("checkpoint B\n");
	//ft_printlex(ms->lex);
	//ft_printct(ms);
	//ft_printf("checkpoint C\n");
	//

	//need better split from piscine
	//need to handle quotes as well. ""
	//replace with lexer/parser maybe?
	if (ft_bonus_executor(ms))
	{
		ft_printf_fd(2, "Executor error\n");
	}
	//ft_printlex(ms->exe);
	//ft_printf("checkpoint D\n");
}

int	minishell(t_ms *ms)
{
	while (ms->live)
	{
		//ft_printf("status: %i\n", ms->error);
		signal(SIGINT, ft_newline);
		ms->s = readline(ms->prompt);
		if(!ms->s)
		{
			ft_free(ms);
			//ft_printf("checkpoint EXIT\n");
			break ;
		}
		else
		{
			if (ms->s[0])
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

	(void)argc;
	(void)argv;
	g_signal = 0;
	ms.ev = env;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_newline);
	ft_init(&ms);
	return (minishell(&ms));
}
