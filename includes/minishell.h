/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:56:30 by tlukanie          #+#    #+#             */
/*   Updated: 2023/07/31 17:35:43 by okraus           ###   ########.fr       */
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

// DEFINITIONS

//# define PROMPT1 "\001\033[1;38:5:51m\002Mini\001\033[0m\033[37m\002\001\033[5m🐧 🪟 🇺🇦🍏🍎\033[0m\002"
# define PROMPT1 "\001\033[1;38:5:51m\002Mini\001\033[0m\033[37m\002\001\033[5m🐧\033[0m\002"
# define PROMPT2 "\001\033[0m\033[1;38:5:226m\002hell\001\033[0m\002:\001\033[1;38:5:46m\002"
# define PROMPT3 "\001\033[0m\002$ \a\a"

// STRUCTURES
// MINISHELL structure

typedef struct s_ms
{
	int		ac;
	int		fdi;
	int		fdo;
	int		fde;
	int		arg;
	int		hd;
	int		live;
	int		err[2];
	int		exit;
	int		*pids;
	int		**pipes;
	char	*prompt;
	char	*s;
	char	**av;
	char	**ev;
	t_list	*el;
	t_list	*lex;
	char	**paths;
	char	***args;
}	t_ms;

// typedef struct s_ms
// {
// 	int		ac;			//argc
// 	int		fdi;		//fd of input
// 	int		fdo;		//fd of output
// 	int		fde;		//fd of error
//	int		arg;		//number of arguments
//	int		hd;			//1 if argv[1] == "here_doc"
//	int		live;		//1 if minishell works, 0 after exit
//	int		err[2];		//errno of builtins; [0] contains errno, [1] contains atatus if it should be deleted 
//	int		exit;		// exit status of exit command	
//	int		*pids;		//pids of child processes
//	int		**pipes;	//pipe fds
//	char	*prompt;	//prompt
//	char	*s;			//last string from user
// 	char	**av;		//*argv[]
// 	char	**ev;		//*envp[]
//	t_list	*el;		// first item in environment list
// 	char	**paths;	//array of paths from envp
// 	char	***args;	//array of arrays of arguments
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
	int		type;
	char	*text;
}	t_token;

typedef enum e_type
{
	NOQUOTE = 0,
	SINGLEQUOTE = 1,
	DOUBLEQUOTE = 2,
	INFILE = 3,
	OUTFILE = 4,
	HEREDOC = 5,
	APPEND = 6,
	PIPE = 7,
	AND = 8,
	OR = 9,
	OPENPAR = 10,
	CLOSEPAR = 11,
	ERRFILE = 12,
	ERRAPPEND = 13,
	INOUTFILE = 14,
	SPACETOKEN = 15
}	t_type;

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
void	ft_exit(t_ms *ms, char *argv[]);

//		ft_export.c
void	ft_export(t_ms *ms, char *argv[]);

//		ft_pwd.c
void	ft_pwd(t_ms *ms, char *argv[]);

//		ft_unset.c
void	ft_unset(t_ms *ms, char *argv[]);
void	ft_free_ev(void *ptr);

//	minishell prototypes

//		ft_expansion.c
char	*ft_expand(t_ms *ms, char *s);

//		ft_lexer.c
t_list	*ft_lexer(t_ms *ms);

//		ft_parser.c
int		ft_parser(t_ms *ms);

//		ft_signal.c
void	ft_newline(int signal);

//	utils prototypes

//		ft_free.c
void	ft_free(t_ms *ms);

//		ft_envval.c
void	ft_putenv(t_list *el);
void	ft_changeenvval(t_ms *ms, char *var, char *val);
char	*ft_getenvval(t_ms *ms, char *var);
char	**ft_list2split(t_list *lst);

//		ft_init.c
void	ft_init(t_ms *ms);
void	ft_init_prompt(t_ms *ms);
t_ev	*ft_evinit(char *str);
void	ft_sortenv(t_list *el);

#endif
