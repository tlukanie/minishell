/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:30:10 by okraus            #+#    #+#             */
/*   Updated: 2023/07/19 16:11:54 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_prompt(t_ms *ms)
{
	char	cwd[4096];
	char	*s;
	char	*h;

	h = ft_getenvval(ms, "HOME");
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

static t_ev	*ft_evinit(char *str)
{
	t_ev	*ev;
	int		i;

	i = 0;
	ev = malloc(sizeof(t_ev));
	if (!ev)
		return (NULL);
	ev->s = ft_stringcopy(str);
	ev->var = ft_stringcopy(str);
	while (ev->var[i] && ev->var[i] != '=')
		i++;
	if (ev->var[i] == '=')
	{
		ev->val = &ev->var[i + 1];
		ev->var[i] = 0;
	}
	else
		ev->val = NULL;
	ev->vals = ft_split(ev->val, ':');
	return (ev);
}

static t_list	*ft_split2list(char **esplit)
{
	int		i;
	t_list	*lstart;
	t_list	*lst;
	t_ev	*ev;

	i = 1;
	ev = ft_evinit(esplit[0]);
	if (!ev)
	{
		//something clever
	}
	lstart = ft_lstnew((void *)ev);
	if (!lstart)
	{
		//something clever
	}
	while (esplit[i])
	{
		ev = ft_evinit(esplit[i]);
		if (!ev)
		{
			//something clever
		}
		lst = ft_lstnew((void *)ev);
		if (!lst)
		{
			//something clever
		}
		ft_lstadd_back(&lstart, lst);
		i++;
	}
	return (lstart);
}

static void	ft_sortenv(t_list *el)
{
	int		sort;
	t_list	*lst;
	t_ev	*enow;
	t_ev	*enext;

	sort = 1;
	while (sort)
	{
		sort = 0;
		lst = el;
		while (lst->next)
		{
			enow = lst->content;
			if (lst->next)
				enext = lst->next->content;
			if (ft_strncmp(enow->var, enext->var, 1024) > 0)
			{
				lst->content = enext;
				lst->next->content = enow;
				sort = 1;
			}
			lst = lst->next;
		}
	}
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
	ms->el = ft_split2list(ms->ev);
	ft_sortenv(ms->el);
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
