/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:14:07 by okraus            #+#    #+#             */
/*   Updated: 2023/07/14 17:42:18 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_cdnew(t_ms *ms, char *argv[])
{
	char	cwd[4096];
	int		r;
	char	*t;

	t = getcwd(cwd, 4096);
	//error check if environmental variables are missing?
	r = chdir(argv[1]);
	if (r < 0)
	{
		r = errno;
		perror("cd: "); // check if this is the correct error call
	}
	else
	{
		// update env
		//ft_printf("changing to newpwd\n");
		ft_changeenvvar(ms, "OLDPWD", t);
		t = getcwd(cwd, 4096);
		ft_changeenvvar(ms, "PWD", t);
		free(ms->prompt);
		ft_init_prompt(ms);
	}
	return (r);
}

static int	ft_cdold(t_ms *ms)
{
	char	cwd[4096];
	int		r;
	char	*o;
	char	*t;

	t = getcwd(cwd, 4096);
	o = ft_getenvvar(ms, "OLDPWD");
	//error check if environmental variables are missing?
	r = chdir(o);
	if (r < 0)
	{
		r = errno;
		perror("cd"); // check if this is the correct error call
	}
	else
	{
		// update env
		//ft_printf("changing to oldpwd\n");
		ft_changeenvvar(ms, "OLDPWD", t);
		t = getcwd(cwd, 4096);
		ft_changeenvvar(ms, "PWD", t);
		free(ms->prompt);
		ft_init_prompt(ms);
		ft_printf("%s\n", t);
	}
	return (r);
}

static int	ft_cdhome(t_ms *ms)
{
	char	cwd[4096];
	int		r;
	char	*h;
	char	*t;

	t = getcwd(cwd, 4096);
	h = ft_getenvvar(ms, "HOME");
	r = chdir(h);
	if (r < 0)
	{
		r = errno;
		perror("cd"); // check if this is the correct error call
	}
	else
	{
		// update env
		//ft_printf("changing to home\n");
		ft_changeenvvar(ms, "OLDPWD", t);
		t = getcwd(cwd, 4096);
		ft_changeenvvar(ms, "PWD", t);
		free(ms->prompt);
		ft_init_prompt(ms);
		//ft_printf("%s\n", t);
	}
	return (r);
}

void	ft_cd(t_ms *ms, char *argv[])
{
	int		r;

	r = 0;
	if (!argv[1] || (argv[1][0] == '-' && argv[1][1] == '-' && !argv[1][2]))
		ft_cdhome(ms);
	else if (argv[2])
	{
		ft_printf_fd(2, "cd: too many arguments\n");
		r = 1;
	}	
	else if (argv[1][0] == '-' && !argv[1][1])
		r = ft_cdold(ms);
	else
		r = ft_cdnew(ms, argv);
	ft_free_split(argv);
	ms->err[0] = r;
	ms->err[1] = 1;
}
