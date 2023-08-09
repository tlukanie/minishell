/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:51:22 by okraus            #+#    #+#             */
/*   Updated: 2023/08/09 19:47:13 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_update_lst(t_list **lst, char *s, int hidden)
{
	t_list	*leaf;

	if (!s || (!ft_strncmp(s, ".", 2) || !ft_strncmp(s, "..", 3)))
		return ;
	if (s[0] == '.' && !hidden)
		return ;
	leaf = ft_lstnew(s);
	if (!*lst)
		*lst = leaf;
	else
		ft_lstadd_back(lst, leaf);
}

static t_list	*ft_get_dir(int mode)
{
	struct dirent	*dp;
	struct stat     statbuf;
	t_list			*lst;
	char			*s;
	DIR				*dir;

	dir = opendir(".");
	lst = NULL;
	if (dir == NULL)
	{
		perror("opendir() error");
		return NULL;
	}
	while ((dp = readdir(dir)) != NULL)
	{
		if (lstat(dp->d_name, &statbuf) == -1)
			continue;
		s = dp->d_name;
		ft_update_lst(&lst, s, mode);
	}
	closedir(dir);
	return (lst);
}

static void	ft_print_dir(t_list *lst)
{
	char	*s;

	while (lst)
	{
		s = lst->content;
		ft_printf("dir: <%s>\n", s);
		lst = lst->next;
	}
}

static void	ft_delstring(void *ptr)
{
	char	*s;

	s = ptr;
	//if (s)
	//	free(s);
	s = NULL;	
}

static int	ft_wild_fits(char *w, char *s)
{
	int	i;
	int j;
	int stop;

	i = 0;
	j = 0;
	ft_printf("s = <%s>\n", s);
	ft_printf("w = <%s>\n", w);
	while (s && w && s[i] && w[j])
	{
		while(s[i] == '*')
			i++;
		stop = i;
		ft_printf("BW:s[i] = <%s> i = %i\n", &s[i], i);
		ft_printf("BW:w[j] = <%s> j = %i\n", &w[j], j);	
		while(w[j] == s[i])
		{
			i++;
			j++;
		}
		ft_printf("AW:s[i] = <%s> i = %i\n", &s[i], i);
		ft_printf("AW:w[j] = <%s> j = %i\n", &w[j], j);
		if (s[i] == 127) //not cool
			s[i] = 0;
		if (s[i] != '*' && s[i])
		{
			ft_printf("s[i] = %i\n", s[i]);
			i = stop;
			j++;
		}
	}
	while(s[i] == '*')
		i++;
	ft_printf("s[i] = <%s> i = %i\n", &s[i], i);
	ft_printf("w[j] = <%s> j = %i\n", &w[j], j);
	if (!s[i])
		return (1);
	return (0);
}

static void	ft_compare(char *s, t_list **dir)
{
	t_list	*lst;
	t_list	*plst;	//previous list
	char	*w;		//wildcard possibility

	lst = *dir;
	plst = NULL;
	while (lst)
	{
		w = lst->content;
		if (!ft_wild_fits(w, s))
		{
			if (plst)
			{
				plst->next = lst->next;
				ft_lstdelone(lst, ft_delstring);
				lst = plst->next;
			}
			else
			{
				*dir = lst->next;
				ft_lstdelone(lst, ft_delstring);
				lst = *dir;
			}			
		}
		else
		{
			plst = lst;
			lst = lst->next;
		}
	}
}

static void	ft_replace_wild(t_list *lst, t_token *token, char *s)
{
	(void)lst;
	(void)token;
	t_list	*dir;

	if (s && s[0] != '.')
		dir = ft_get_dir(0);
	else
		dir = ft_get_dir(1);

	ft_print_dir(dir);
	ft_compare(s, &dir);
	ft_printf("\nnew\n");
	ft_print_dir(dir);
	//create list of stuff in current folder (if s[0] = '.' with hidden files)
	//exclude . and ..
	//compare string with list, delete from the list what does not fit
	//if nothing left nothing changed
	//if something left replace current token with space and insert new list of tokens
	//(SPACE NOQUOTE SPACE ... SPACE NOQUOTE SPACE)
	//insert list function
	//delete dir;
	
}

void	ft_expand_wild(t_ms *ms, t_list *lst)
{
	int		i;
	char	*s;
	t_token	*token;

	(void)ms;
	token = lst->content;
	if (token->type == NOQUOTE)
	{
		i = 0;
		s = token->text;
		while (s && s[i])
		{
			if (s[i] == '*')
				ft_replace_wild(lst, token, s);
			i++;
		}
	}
}
