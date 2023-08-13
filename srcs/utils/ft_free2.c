/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:33:37 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/13 20:33:49 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_mini_free(t_ms *ms)
{
	if (ms->lex)
		ft_lstclear(&ms->lex, ft_free_token);
	ms->lex = NULL;
	if (ms->exe)
		ft_lstclear(&ms->exe, ft_free_token);
	ms->exe = NULL;
	if (ms->csn)
		ft_free_cs(ms);
	ms->csn = 0;
}

void	ft_exit(t_ms *ms, int err)
{
	static t_ms	*stat;

	if (!stat)
		stat = ms;
	else
	{
		ft_free(stat);
		exit(err);
	}
}
