/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/08/13 19:59:27 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_cdnew(t_ms *ms, char *argv[])
{
	char	cwd[4096];
	int		r;
	char	*t;
	char	*err;

	t = getcwd(cwd, 4096);
	r = chdir(argv[1]);
	if (r < 0)
	{
		r = errno;
		err = ft_strjoin("minishell: cd: ", argv[1]);
		perror(err);
		free(err);
	}
	else
	{
		ft_changeenvval(ms, "OLDPWD", t);
		t = getcwd(cwd, 4096);
		ft_changeenvval(ms, "PWD", t);
		free(ms->prompt);
		ft_init_prompt(ms);
	}
	return (r);
}

static void	ft_update_cdold(t_ms *ms, char *t, char *cwd)
{
	ft_changeenvval(ms, "OLDPWD", t);
	t = getcwd(cwd, 4096);
	ft_changeenvval(ms, "PWD", t);
	free(ms->prompt);
	ft_init_prompt(ms);
	ft_printf("%s\n", t);
}

static int	ft_cdold(t_ms *ms)
{
	char	cwd[4096];
	int		r;
	char	*o;
	char	*t;

	t = getcwd(cwd, 4096);
	o = ft_getenvval(ms, "OLDPWD");
	if (!o)
	{
		r = 1;
		ft_printf_fd(2, "minishell: cd: OLDPWD not set\n");
		return (r);
	}
	r = chdir(o);
	if (r < 0)
	{
		r = errno;
		perror("cd");
	}
	else
		ft_update_cdold(ms, t, cwd);
	return (r);
}

static int	ft_cdhome(t_ms *ms)
{
	char	cwd[4096];
	int		r;
	char	*h;
	char	*t;

	t = getcwd(cwd, 4096);
	h = ft_getenvval(ms, "HOME");
	r = chdir(h);
	if (r < 0)
	{
		r = errno;
		perror("cd");
	}
	else
	{
		ft_changeenvval(ms, "OLDPWD", t);
		t = getcwd(cwd, 4096);
		ft_changeenvval(ms, "PWD", t);
		free(ms->prompt);
		ft_init_prompt(ms);
	}
	return (r);
}

void	ft_cd(t_ms *ms, char *argv[])
{
	int	r;

	r = 0;
	if (!argv[1] || (argv[1][0] == '-' && argv[1][1] == '-' && !argv[1][2]))
		ft_cdhome(ms);
	else if (argv[2])
	{
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
		r = 1;
	}
	else if (argv[1][0] == '-' && !argv[1][1])
		r = ft_cdold(ms);
	else
		r = ft_cdnew(ms, argv);
	ms->err[0] = r;
	ms->error = r;
	ms->err[1] = 1;
}
