/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:32:30 by okraus            #+#    #+#             */
/*   Updated: 2023/08/07 17:26:15 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//should check if file exists and is accessible for writing
int	ft_fillctfd(t_ct *ct, char *file, int *r)
{
	if (*r & INFILE)
	{
		if (!access(file, F_OK & R_OK))
		{
			if (ct->fds[0][0] > 2)
				close(ct->fds[0][0]);
			ct->fds[0][0] = open(file, O_RDONLY);
			ct->fds[0][1] = 1;
		}
		else
		{
			ct->fds[0][0] = -1;
			perror(file);
			return (1);
		}
		if (ct->hd)
			ct->hd = NULL;
	}
	else if (*r & HEREDOC)
	{
		if (ct->fds[0][0] > 2)
			close(ct->fds[0][0]);
		ct->hd = file;
		ct->fds[0][1] = 2;
	}
	else if (*r & OUTFILE)
	{
		if (ct->fds[1][0] > 2)
			close(ct->fds[1][0]);
		ct->fds[1][0] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ct->fds[1][1] = 1;
	}
	else if (*r & APPEND)
	{
		if (ct->fds[1][0] > 2)
			close(ct->fds[1][0]);
		ct->fds[1][0] = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		ct->fds[1][1] = 2;
	}
	else if (*r & ERRFILE)
	{
		if (ct->fds[2][0] > 2)
			close(ct->fds[2][0]);
		ct->fds[2][0] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ct->fds[2][1] = 1;
	}
	else if (*r & ERRAPPEND)
	{
		if (ct->fds[2][0] > 2)
			close(ct->fds[2][0]);
		ct->fds[2][0] = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		ct->fds[2][1] = 2;
	}
	else if (*r & INOUTFILE)
	{
		ft_printf("<> not implemented\n");
	}
	*r = 0;
	return (0);
}

int	ft_fillct(t_ct *ct, char *text, int *r)
{
	if (!(*r))
	{
		//ft_printf("ABC\n");
		if (!ct->argv && text)
		{
			ct->argv = malloc(sizeof(char *) * 2);
			if(!ct->argv)
			{
				//ft_printf("err1\n");
				return (1);
			}
			ct->argv[0] = ft_stringcopy(text);
			if (!ct->argv[0])
			{
				//ft_printf("err2\n");
				return (1);
			}
			ct->argv[1] = NULL;
		}
		else if (ct->argv && text)
		{
			if (ft_split_add(&ct->argv, text, ft_splitlen(ct->argv)))
			{
				//ft_printf("text: %s\n", text);
				//ft_printf("argv: %s\n", ct->argv[0]);
				//ft_printf("argv: %s\n", ct->argv[1]);
				ft_printf("err3\n");
				return (1);
			}
		}
		if (ct->argv)
		{
			//ft_printf("%s\n", text);
			//ft_put_split(ct->argv);
		}
	}
	else
	{
		//ft_printf("redirecting\n");
		if (ft_fillctfd(ct, text, r))
		{
			//ft_printf("err4\n");
			return (2);
		}
	}
	//ft_printf("all good\n");
	return (0);
}

int	ft_fillcts(t_ms *ms)
{
	t_list			*lst;
	t_token			*token;
	unsigned int	i;		//iterate over command structures
	int				j;		//iterate over command tables
	int				r;		//redirect flag

	lst = ms->lex;
	i = 0;
	r = 0;
	j = 0;
	//ft_printf("D1\n");
	while (lst)
	{
		token = lst->content;
		//ft_printf("D2\n");
		if (token->type & ANDOR)
		{
			j = 0;
			i++;
			ms->cs[i].ct[j].argv = NULL;
		}
		else if (token->type & PIPE)		
			j++;
		else if (token->type & REDIRECTS)
			r = token->type & REDIRECTS;
		else if (token->type & TEXT)
		{
			//ft_printf("%p\n", ms->cs[i].ct[j].argv);
			if (ft_fillct(&(ms->cs[i].ct[j]), token->text, &r))
			{
				return(1);
			}
		}
		// the next string after redirect affects fds
		//otherwise add text to argv in cs[i].ct[j];
		//function to fill stuff (maybe r could be static variable in it)
		lst = lst->next;
	}
	return (0);
}

void ft_updatecsn(t_ms *ms)
{
	t_list			*lst;
	t_token			*token;
	unsigned int	i;

	i = 0;
	lst = ms->lex;
	while (lst)
	{
		token = lst->content;
		if (token->type & ANDOR)
			i++;
		token->type |= 0x10000U * i;
		lst = lst->next;
	}
	ms->csn = i + 1;
}

int	ft_createct(t_ms *ms)
{
	t_ct	*ct;
	int		i;
	int		j;

	i = 0;
	
	while (i < ms->csn)
	{
		ct = malloc(sizeof(t_ct) * (ms->cs[i].ctn));
		if (!ct)
			return (1);
		j = 0;
		while (j < ms->cs[i].ctn)
		{
			ct[j].fds[0][0] = 0;
			ct[j].fds[0][1] = 0;
			ct[j].fds[1][0] = 1;
			ct[j].fds[1][1] = 0;
			ct[j].fds[2][0] = 2;
			ct[j].fds[2][1] = 0;
			ct[j].hd = NULL;
			ct[j].hdpipe[0] = 0;
			ct[j].hdpipe[1] = 0;
			ct[j].argv = NULL;
			j++;	
		}
		ms->cs[i].ct = ct;
		i++;
	}
	return (0);
}

void ft_updatectn(t_ms *ms)
{
	t_list			*lst;
	t_token			*token;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	lst = ms->lex;
	while (lst)
	{
		token = lst->content;
		if (token->type & ANDOR)
		{
			ms->cs[i].ctn = j + 1;
			i++;
			j = 0;
		}
		if (token->type & PIPE)
			j++;
		//ft_printf("i=%u, j=%u\n", i , j);
		lst = lst->next;
	}
	ms->cs[i].ctn = j + 1;  //needs to be one for one command (should add extra check for non text tokens?)
}

int	ft_createcs(t_ms *ms)
{
	t_cs	*cs;

	cs = malloc(sizeof(t_cs) * (ms->csn));
	if (!cs)
		return (1);
	cs->pids = NULL;
	cs->pipes = NULL;
	ms->cs = cs;
	ft_updatectn(ms);
	if (ft_createct(ms))
		return (1);
	return (0);
}

int	ft_parser(t_ms *ms)
{	
	ms->csn = 0;
	ms->cs = NULL;
	//ft_printf("0\n");
	if (!ms->lex)
		return (0);
	if (ft_expand_strings(ms))
		return (1);
	if (ft_jointext(ms))
		return (2);
	// expand wildcards
	// create binary tree
	// count cs & update token type
	ft_updatecsn(ms);
	// create a command structure
	if (ft_createcs(ms))
		return (5);
	//ft_printf("5\n");
	if (ft_fillcts(ms))
	{
		return (6);
	}
	//ft_printf("6\n");
	// update paths probably in other function
	return (0);
}
