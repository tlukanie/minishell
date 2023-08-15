/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:36:35 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/15 14:36:38 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_fillctfd_helper(t_ct *ct, char *file, int fd, unsigned int type)
{
    if (ct->fds[fd][0] > 2)
        close(ct->fds[fd][0]);
    if (type & (OUTFILE | ERRFILE))
        ct->fds[fd][0] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (type & (APPEND | ERRAPPEND))
        ct->fds[fd][0] = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else if (type & INFILE)
        ct->fds[0][0] = open(file, O_RDONLY);
    ct->fds[fd][1] = 1;
}

int ft_fillctfd_helper_err(t_ct *ct, char *file, int *r, int fd)
{
    ct->fds[fd][0] = -1;
	ct->fds[fd][1] = -1;
	ft_printf_fd(2, "minishell: %s: %s\n", file, strerror(errno));
	*r = 0;
	return (0);
}

int	ft_fillctfd(t_ct *ct, char *file, int *r)
{
	if (*r & INFILE)
	{
		if (!access(file, F_OK | R_OK))
            ft_fillctfd_helper(ct, file, 0, INFILE);
		else
            ft_fillctfd_helper_err(ct, file, r, 0);
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
		if (!access(file, F_OK | W_OK))
            ft_fillctfd_helper(ct, file, 1, OUTFILE);
		else
            ft_fillctfd_helper_err(ct, file, r, 1);		
	}
	else if (*r & APPEND)
	{
		if (!access(file, F_OK | W_OK))
            ft_fillctfd_helper(ct, file, 1, APPEND);
		else
            ft_fillctfd_helper_err(ct, file, r, 1);	
	}
	else if (*r & ERRFILE)
	{
		if (!access(file, F_OK | W_OK))
            ft_fillctfd_helper(ct, file, 2, ERRFILE);
		else
            ft_fillctfd_helper_err(ct, file, r, 2);	
	}
	else if (*r & ERRAPPEND)
	{
		if (!access(file, F_OK | W_OK))
            ft_fillctfd_helper(ct, file, 2, ERRAPPEND);
		else
            ft_fillctfd_helper_err(ct, file, r, 2);	
	}
	else if (*r & INOUTFILE)
	{
		ft_printf("<> not implemented\n");
	}
	*r = 0;
	return (0);
}