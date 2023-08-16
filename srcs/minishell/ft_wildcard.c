/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:51:22 by okraus            #+#    #+#             */
/*   Updated: 2023/08/16 15:04:41 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_lst(t_list **lst, char *s, int hidden)
{
	t_list	*leaf;

	if (s[0] == '.' && !hidden)
	{
		free(s);
		return ;
	}
	leaf = ft_lstnew(s);
	if (!*lst)
		*lst = leaf;
	else
		ft_lstadd_back(lst, leaf);
}

t_list	*ft_get_dir(int mode)
{
	struct dirent	*dp;
	struct stat		statbuf;
	t_list			*lst;
	char			*s;
	DIR				*dir;

	dir = opendir(".");
	lst = NULL;
	if (dir == NULL)
	{
		perror("opendir() error");
		return (NULL);
	}
	dp = readdir(dir);
	while (dp)
	{
		if (lstat(dp->d_name, &statbuf) == -1)
			continue ;
		s = ft_stringcopy(dp->d_name);
		ft_update_lst(&lst, s, mode);
		dp = readdir(dir);
	}
	closedir(dir);
	return (lst);
}

void	ft_delstring(void *ptr)
{
	char	*s;

	s = ptr;
	if (s)
		free (s);
	s = NULL;
}
