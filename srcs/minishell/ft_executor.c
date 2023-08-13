/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:11:29 by okraus            #+#    #+#             */
/*   Updated: 2023/08/13 12:26:57 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//test local path then test variable
static char	*ft_pathjoin(char *path, char *cmd)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_calloc(ft_strlen(path) + 2 + ft_strlen(cmd), sizeof(char));
	while (path[i])
	{
		str[i] = path[i];
		i++;
	}
	str[i] = '/';
	i++;
	while (cmd[j])
	{
		str[i + j] = cmd[j];
		j++;
	}
	return (str);
}

static int	ft_exec(t_ms *ms, char **cmd)
{
	int		i;
	int		fail;
	char	*cmdp;
	char	**paths;
	char	**env;

	i = 0;
	fail = 1;
	env = ft_list2split(ms->el);
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, env);
	//ft_printf("%s, %i\n", cmd[0], access(cmd[0], X_OK));
	//ft_put_split(cmd);
	//ft_printf("%s, %i\n", strerror(errno), errno);
	paths = ft_getenvvals(ms, "PATH");
	if (!paths)
		return (fail);
	while (paths[i])
	{
		cmdp = ft_pathjoin(paths[i], cmd[0]);
		if (access(cmdp, X_OK) == 0)
			execve(cmdp, cmd, env);
		free(cmdp);
		i++;
	}
	ft_printf_fd(2, "%s: command not found\n", cmd[0]);
	return (fail);
}

static int	ft_newin(t_ms *ms, int i, int j)
{
	if (ms->cs[i].ct[j].fds[0][1] == 2)
		return (ms->cs[i].ct[j].hdpipe[0]);
	if (j)
	{
		if (ms->cs[i].ct[j].fds[0][1] == 1)
			return (ms->cs[i].ct[j].fds[0][0]);
		else
			return (ms->cs[i].pipes[j - 1][0]);
	}
	if (ms->cs[i].ct[j].fds[0][1] == 1)
		return (ms->cs[i].ct[j].fds[0][0]);
	return (0);
}

static int	ft_newout(t_ms *ms, int i, int j)
{
	if (j < ms->cs[i].ctn - 1)
	{
		if (ms->cs[i].ct[j].fds[1][1])
			return (ms->cs[i].ct[j].fds[1][0]);
		else
			return (ms->cs[i].pipes[j][1]);
	}
	if (ms->cs[i].ct[j].fds[1][1])
			return (ms->cs[i].ct[j].fds[1][0]);
	return (1);
}

static int	ft_newerr(t_ms *ms, int i, int j)
{
	if (ms->cs[i].ct[j].fds[2][1])
			return (ms->cs[i].ct[j].fds[2][0]);
	return (2);
}

static int ft_dup(t_ms *ms, int i, int j)
{
	int newin;
	int newout;
	int newerr;

	newin = ft_newin(ms, i, j);
	newout = ft_newout(ms, i, j);
	newerr = ft_newerr(ms, i, j);
	//printf("Duplicating newin %i, newout %i, newerr %i\n", newin, newout, newerr);
	if (newin > 2)
	{
		//printf("Duplicating input %s\n", ms->cs[i].ct[j].argv[0]);
		if (dup2(newin, STDIN_FILENO) < 0)
		{
			ft_printf_fd(2, "Error duplicating input\n");
			return (1);
		}
	}
	if (newout > 2)
	{
		//printf("Duplicating output %s\n", ms->cs[i].ct[j].argv[0]);
		if (dup2(newout, STDOUT_FILENO) < 0)
		{
			ft_printf_fd(2, "Error duplicating output\n");
			return (2);
		}
	}
	if (newerr > 2)
	{
		//printf("Duplicating error %s\n", ms->cs[i].ct[j].argv[0]);
		if (dup2(newerr, STDERR_FILENO) < 0)
		{
			ft_printf_fd(2, "Error duplicating error output\n");
			return (3);
		}
	}
	return (0);
}
static void	ft_closepipes(t_ms *ms, int i)
{
	int k;

	k = 0;
	if (ms->cs[i].ctn > 1)
	{
		while (k < ms->cs[i].ctn - 1)
		{
			close(ms->cs[i].pipes[k][0]);
			close(ms->cs[i].pipes[k][1]);
			k++;
		}
	}
	k = 0;
	while (k < ms->cs[i].ctn)
	{
		if (ms->cs[i].ct[k].hd)
		{
			if (ms->cs[i].ct[k].hdpipe[0] > 2)
				close(ms->cs[i].ct[k].hdpipe[0]);
			if (ms->cs[i].ct[k].hdpipe[1] > 2)
				close(ms->cs[i].ct[k].hdpipe[1]);
		}
		k++;
	}
}

static void	ft_closefds(t_ms *ms, int i)
{
	int k;

	k = 0;
	while (k < ms->cs[i].ctn)
	{
		if (ms->cs[i].ct[k].fds[0][0] > 2)
			if (close (ms->cs[i].ct[k].fds[0][0]))
				printf("Error closing input %i\n", ms->cs[i].ct[k].fds[0][0]);
		if (ms->cs[i].ct[k].fds[1][0] > 2)
			if (close (ms->cs[i].ct[k].fds[1][0]))
				printf("Error closing output %i\n", ms->cs[i].ct[k].fds[1][0]);
		if (ms->cs[i].ct[k].fds[2][0] > 2)
			if (close (ms->cs[i].ct[k].fds[2][0]))
				printf("Error closing err %i\n", ms->cs[i].ct[k].fds[2][0]);
		k++;
	}
}

static void	ft_heredoc(t_ms *ms, int i, int j)
{
	char	*line;
	int		pid;

	line = NULL;
	if (ms->cs[i].ct[j].hd)
	{
		if (pipe(ms->cs[i].ct[j].hdpipe) == -1)
		{
			ft_printf_fd(2, "Error with creating pipe\n");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
			exit(1); //better exit
		if (pid == 0)
		{
			while (1)
			{
				write (1, "> ", 2);
				line = get_next_line(0);
				if (line == NULL)
				{
					ft_printf_fd(2, "\nminishell: warning: here-document ");
					ft_printf_fd(2, "delimited by end-of-file (wanted");
					ft_printf_fd(2, "`%s')\n", ms->cs[i].ct[j].hd);
					//free!
					exit(1);
				}
				if (ft_strncmp(line, ms->cs[i].ct[j].hd,
					ft_strlen(ms->cs[i].ct[j].hd)) == 0)
					break ;
				write(ms->cs[i].ct[j].hdpipe[1], line, ft_strlen(line));
				free(line);
			}
			free(line);
			ft_closefds(ms, i);
			ft_closepipes(ms, i);
			exit(1); //free before exit
		}
		ft_wait(ms, pid, 0);
	}
}

static int ft_execct(t_ms *ms, int i, int j)
{
	char	**argv;

	argv = ms->cs[i].ct[j].argv;
	if (ms->cs[i].ct[j].fds[0][0] < 0
		|| ms->cs[i].ct[j].fds[1][0] < 0
		|| ms->cs[i].ct[j].fds[2][0] < 0)
	{
		ms->error = 1;
		return (0);
	}
	if (!argv[0])
		return (0);
	if (!ft_strncmp(argv[0], "exit", 5))
	{
		ft_exit_builtin(ms, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "cd", 3))
	{
		ft_cd(ms, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "export", 7))
	{
		ft_export(ms, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "unset", 6))
	{
		ft_unset(ms, argv);
		return (0);
	}
	ms->cs[i].pids[j] = fork();
	ms->parent++;
	//printf("i = %i, j = %i, status = %i, pid = %i\n", i, j, ms->error, ms->cs[i].pids[j]);
	if (ms->cs[i].pids[j] < 0)
		exit(255); //should not happen but needs better handling
	if (ms->cs[i].pids[j] == 0)
	{
		signal(SIGINT, ft_exit_sig);
		ms->child = 1;
		//printf("Heredocking %s\n", argv[0]);
		ft_heredoc(ms, i, j);
		//printf("Duping %s\n", argv[0]);
		if (ft_dup(ms, i, j))
			return (3);
		//printf("Closing %s\n", argv[0]);
		ft_closepipes(ms, i);
		ft_closefds(ms, i);
		//printf("Executing %s\n", argv[0]);
		if (!ft_strncmp(argv[0], "pwd", 4))
			ft_pwd(ms, argv);
		else if (!ft_strncmp(argv[0], "env", 4))
			ft_env(ms, argv);
		else if (!ft_strncmp(argv[0], "echo", 5))
			ft_echo(ms, argv);
		else //execve
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			ft_exec(ms, ms->cs[i].ct[j].argv);
			ft_printf_fd(2, "command not found: %s\n", argv[0]);
			ft_free(ms);
			exit(127);
		}
	}
	else
		signal(SIGINT, ft_global_sig);
	return (0);
}

static int ft_open_pipes(t_ms *ms, int i)
{
	int	j;

	j = 0;
	ms->cs[i].pipes = ft_calloc(sizeof(int[2]), ms->cs[i].ctn - 1);
		if (!ms->cs[i].pipes)
			return (1);
	while (j < ms->cs[i].ctn - 1)
	{
		if (pipe(ms->cs[i].pipes[j]) == -1)
		{
			ft_printf_fd(2, "Error with creating pipe\n");
			return (1);
		}
		j++;
	}
	//ft_printf ("%i pipes opened\n", j);
	return (0);
}

int ft_execcs(t_ms *ms, int i)
{
	int	j;
	int	w;

	j = 0;
	ms->cs[i].pipes = NULL;
	ms->cs[i].pids = NULL;
	if (ms->cs[i].ctn > 1)
	{
		if (ft_open_pipes(ms, i))
			return (1);
	}
	//ft_printf("Opened pipes.\n");
	if (ms->cs[i].ctn)
	{
		ms->cs[i].pids = ft_calloc(sizeof(int), ms->cs[i].ctn);
		if (!ms->cs[i].pids)
			return (1);
	}
	//ft_printf("Created pids.\n");
	while (j < ms->cs[i].ctn)
	{
		if (ft_execct(ms, i, j))
			return (1);
		j++;
	}
	//ft_printf("Executed command tables.\n");
	//printf("Closing parent\n");
	ft_closepipes(ms, i);
	//printf("Closed parent\n");
	w = 0;
	while (w < ms->cs[i].ctn)
	{
		if (ms->cs[i].pids[w])
		{
			//printf("Waiting for pid %i.\n", ms->cs[i].pids[w]);
			ft_wait(ms, ms->cs[i].pids[w], 0);
			//printf("status is %i\n", ms->error);
			//printf("Waited for pid %i.\n", ms->cs[i].pids[w]);
		}
		w++;
	}
	free(ms->cs[i].pids);
	ms->cs[i].pids = NULL;
	ft_closefds(ms, i);
	//printf("Waited for all waitpids.\n");
	return (0);
}

int	ft_executor(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < ms->csn)
	{
		if (ft_execcs(ms, i))
			return (1);
		i++;
		//ft_printf("%i. command structure executed successfully\n", i);
	}
	return (0);
}