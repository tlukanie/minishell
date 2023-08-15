/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 21:07:18 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/15 21:07:21 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_wild_fits(char *w, char *s)
{
	int	i;
	int j;
	int stopi;
	int stopj;

	i = 0;
	j = 0;
    
	if (s && w)
	{
		while(s[i] != '*')
		{
			if (s[i] != w[j])
				return (0);
			i++;
			j++;
		}
	}
	while (s && w && s[i] && w[j])
	{
		while(s[i] == '*')
			i++;
		stopi = i;
		stopj = j;	
		while(w[j] && w[j] == s[i])
		{
			i++;
			j++;
		}
		if ((s[i] != '*' && s[i]) || (w[j] && s[i] != '*'))
		{
			i = stopi;
			j = stopj + 1;
		}
	} 
	while(s[i] == '*')
		i++;
	if ((!s[i] && s[i - 1] !='*' && !w[j]) || (!s[i] && s[i - 1] == '*'))
		return (1);
	return (0);
}
