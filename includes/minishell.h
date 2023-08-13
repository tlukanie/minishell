/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:56:30 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/13 15:47:48 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

// INCLUDES

# include "../libft/header/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>


// DEFINITIONS

//# define PROMPT1 "\001\033[1;38:5:51m\002Mini\001\033[0m\033[37m\002\001\033[5m🐧 🪟 🇺🇦🍏🍎\033[0m\002"
# define PROMPT1 "\001\033[1;38:5:51m\002Mini\001\033[0m\033[37m\002\001\033[5m🐧\033[0m\002"
# define PROMPT2 "\001\033[0m\033[1;38:5:226m\002shell\001\033[0m\002:\001\033[1;38:5:46m\002"
# define PROMPT3 "\001\033[0m\002$ \a\a"

// STRUCTURES
// MINISHELL structure

extern int g_signal;

typedef struct s_cs
	t_cs;

typedef struct s_ms
{
	int		live;
	int		signal;
	int		parent;
	int		child;
	int		err[2];		//remove this array
	int		error;
	int		exit;
	int		csn;
	char	*prompt;
	char	*pwd;		//need to initialize
	char	*s;
	char	**ev;
	t_cs	*cs;
	t_list	*el;
	t_list	*lex;
	t_list	*exe;
}	t_ms;

// typedef struct s_ms
// {
//	int		arg;		//number of arguments
//	int		hd;			//1 if argv[1] == "here_doc"
//	int		live;		//1 if minishell works, 0 after exit
//	int		err[2];		//errno of builtins; [0] contains errno, [1] contains atatus if it should be deleted 
//	int		exit;		// exit status of exit command	
//	int		csn;		//number of command groups
//	t_cs	*cs;		//command structure
//	char	*prompt;	//prompt
//	char	*s;			//last string from user
// 	char	**ev;		//*envp[]
//	t_list	*el;		// first item in environment list
// 	char	**paths;	//array of paths from envp
// }	t_ms;

typedef struct s_ev
{
	char	*s;
	char	*var;
	char	*val;
	char	**vals;
}	t_ev;

// typedef struct s_ev
// {
// 	char	*s;		//	"V1=1:2:3"
// 	char	*var;	//	"V1"
// 	char	*val;	//	"1:2:3"
// 	char	**vals;	//	"1", "2", "3", NULL
// }	t_ev;

typedef struct s_token
{
	unsigned int	type;
	int				csi; //command structure index;
	char			*text;
}	t_token;

typedef enum e_type
{
	SINGLEQUOTE = 0x1,	// ...0000 0001
	DOUBLEQUOTE = 0x2,	// ...0000 0010
	NOQUOTE = 0x4,		// ...0000 0100
	PIPE = 0x8,
	INFILE = 0x10,
	HEREDOC = 0x20,
	OUTFILE = 0x40,
	APPEND = 0x80,
	ERRFILE = 0x100,
	ERRAPPEND = 0x200,
	INOUTFILE = 0x400,
	SPACETOKEN = 0x800,
	AND = 0x1000,
	OR = 0x2000,
	OPENPAR = 0x4000,
	CLOSEPAR = 0x8000,
	TEXT = 0x7,			// ...0000 0111
	ANDOR = 0x3000,		
	REDIRECTS = 0x7F0,
	PAR = 0xC000,
	BONUS = 0xFFFF0000 //mask to index of the command group
}	t_type;

typedef struct s_checker
{
	t_token	*token;
	int		text;
	int		stuff; //no space and no text;
	int		parentheses;
	int		status;
}	t_check;

//command table = ct
typedef struct s_ct
{
	char	**argv;
	char	*hd;			//here doc
	int		hdpipe[2];		//pipe for heredoc
	int		fds[3][2];
}	t_ct;

// typedef struct s_ct
// {
// 	char	**argv;		// argv[0] = command, argv[i] = arguments
// 	int		fds[3][2];	// 0 fd:	0 STDIN, 1 STDOUT, 2 STDERR, FD
// }	t_ct;			// 1 mode:	0-normal, 1 TRUNC, 2 APPEND/HERE_DOC
//	fds[0][0] = 0	//standard input on file descriptor 0
//	fds[0][1] = 2	//mode 2 << here doc (if here doc, the first one will count how many here docs are there)
//	fds[1][0] = fd	//standard output on file descriptor of outfile
//	fds[1][1] = 1	//mode TRUNC (overwrite)
//	fds[2][0] = 2	//standard error on file descriptor 2
//	fds[2][1] = 0	//mode standard

//command structure = cs - needed for parsing pipes and redirections
typedef struct s_cs
{
	int		ctn;			//number of command tables (pipe count + 1)
	int		*pids;			//child processes for the execution of the commands
	int		(*pipes)[2];	//fds of pipes
	t_ct	*ct;			//command tables for the child process
}	t_cs;

//	PROTOTYPES

//	minishell prototypes

//		ft_minishell.c
int		minishell(t_ms *ms);

//	builtins prototypes

//		ft_cd.c
void	ft_cd(t_ms *ms, char *argv[]);

//		ft_echo.c
void	ft_echo(t_ms *ms, char *argv[]);

//		ft_env.c
void	ft_env(t_ms *ms, char *argv[]);

//		ft_exit.c
void	ft_exit_builtin(t_ms *ms, char *argv[]);

//		ft_export.c
void	ft_export(t_ms *ms, char *argv[]);

//		ft_pwd.c
void	ft_pwd(t_ms *ms, char *argv[]);

//		ft_unset.c
void	ft_unset(t_ms *ms, char *argv[]);

//	minishell prototypes

//		ft_bonus_exe.c
int		ft_bonus_executor(t_ms *ms);

//		ft_executor.c
int		ft_executor(t_ms *ms);
int 	ft_execcs(t_ms *ms, int i);

//		ft_expansion.c
char	*ft_expand(t_ms *ms, char *s);

//		ft_lexer.c
t_list	*ft_lexer(t_ms *ms);

//		ft_parser.c
int		ft_parser(t_ms *ms);

//		ft_parsetext.c
int		ft_jointext(t_ms *ms);
int		ft_expand_strings(t_ms *ms);

//		ft_signal.c
void	ft_newline(int signal);
void	ft_newnewline(int signal);
void	ft_global_sig(int signal);
void	ft_exit_sig(int signal);

//		ft_tokenchecker.c
int		ft_tokenchecker(t_ms *ms);

//		ft_wildcard.c
void	ft_expand_wild(t_ms *ms, t_list *lst);

//	utils prototypes

//		ft_free.c
void	ft_free_ev(void *ptr);
void	ft_free_token(void *ptr);
void	ft_mini_free(t_ms *ms);
void	ft_free(t_ms *ms);
void	ft_exit(t_ms *ms, int err);
void	ft_free_cs(t_ms *ms);

//		ft_envval.c
void	ft_putenv(t_list *el);
void	ft_changeenvval(t_ms *ms, char *var, char *val);
char	*ft_getenvval(t_ms *ms, char *var);
char	**ft_getenvvals(t_ms *ms, char *var);
char	**ft_list2split(t_list *lst);

//		ft_init.c
void	ft_init(t_ms *ms);
void	ft_init_prompt(t_ms *ms);
t_ev	*ft_evinit(char *str);
void	ft_sortenv(t_list *el);

//		ft_wait.c
void	ft_wait(t_ms *ms, int pid, int options);

#endif
