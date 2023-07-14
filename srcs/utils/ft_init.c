/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:30:10 by okraus            #+#    #+#             */
/*   Updated: 2023/07/14 17:31:06 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_prompt(t_ms *ms)
{
	char	cwd[4096];
	char	*s;
	char	*h;

	h = ft_getenvvar(ms, "HOME");
	s = getcwd(cwd, 4096);
	if (h && !ft_strncmp(s, h, ft_strlen(h)))
	{
		s = s + (ft_strlen(h) - 1);
		s[0] = '~';
	}
	ms->prompt = ft_strjoin(PROMPT1, PROMPT2);
	ms->prompt = ft_strjoin_freeleft(ms->prompt, s);
	ms->prompt = ft_strjoin_freeleft(ms->prompt, PROMPT3);
}

void	ft_init(t_ms *ms)
{
	ms->live = 1;
	ms->err[0] = 0;
	ms->err[1] = 0;
	ms->exit = 0;
	ms->pids = NULL;
	ms->pipes = NULL;
	ft_init_prompt(ms);
	ms->s = NULL;
	ms->paths = NULL;
	ms->args = NULL;
	ms->ev = ft_copy_split(ms->ev);
}

// typedef struct s_ms
// {
// 	int		ac;			//argc
// 	int		fdi;		//fd of input
// 	int		fdo;		//fd of output
// 	int		fde;		//fd of error
//	int		arg;		//number of arguments
//	int		hd;			//1 if argv[1] == "here_doc"
//	int		live		//1 if minishell works, 0 after exit
//	int		*pids;		//pids of child processes
//	int		**pipes;	//pipe fds
//	char	*prompt;	//prompt
// 	char	**av;		//*argv[]
// 	char	**ev;		//*envp[]
// 	char	**paths;	//array of paths from envp
// 	char	***args;	//array of arrays of arguments
// }	t_ms;
