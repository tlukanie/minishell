/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:56:30 by tlukanie          #+#    #+#             */
/*   Updated: 2023/08/16 14:59:27 by tlukanie         ###   ########.fr       */
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

# define PROMPT1 \
"\001\033[1;38:5:51m\002Mini\001\033[0m\033[37m\002\001\033[5m🐧\033[0m\002"
# define PROMPT2 \
"\001\033[0m\033[1;38:5:226m\002shell\001\033[0m\002:\001\033[1;38:5:46m\002"
# define PROMPT3 "\001\033[0m\002$ \a\a"

// STRUCTURES
// MINISHELL structure

extern int			g_signal;

typedef struct s_cs	t_cs;

typedef struct s_ms
{
	int		live;
	int		signal;
	int		parent;
	int		child;
	int		err[2];
	int		error;
	int		exit;
	int		csn;
	char	*prompt;
	char	*pwd;
	char	*s;
	char	**ev;
	t_cs	*cs;
	t_list	*el;
	t_list	*lex;
	t_list	*exe;
}	t_ms;

typedef struct s_ev
{
	char	*s;
	char	*var;
	char	*val;
	char	**vals;
}	t_ev;

typedef struct s_token
{
	unsigned int	type;
	int				csi;
	char			*text;
}	t_token;

typedef enum e_type
{
	SINGLEQUOTE = 0x1,
	DOUBLEQUOTE = 0x2,
	NOQUOTE = 0x4,
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
	TEXT = 0x7,
	ANDOR = 0x3000,		
	REDIRECTS = 0x7F0,
	PAR = 0xC000,
	BONUS = 0xFFFF0000
}	t_type;

typedef struct s_checker
{
	t_token	*token;
	int		text;
	int		stuff;
	int		parentheses;
	int		status;
}	t_check;

//command table = ct
typedef struct s_ct
{
	char	**argv;
	char	*hd;
	int		hdpipe[2];
	int		fds[3][2];
}	t_ct;

typedef struct s_cs
{
	int		ctn;
	int		*pids;
	int		(*pipes)[2];
	t_ct	*ct;
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
t_list	*ft_run_parentheses(t_ms *ms, t_list *ex);
int		ft_bonus_exe_loop(t_ms *ms);

//		ft_executor.c
int		ft_executor(t_ms *ms);
int		ft_execcs(t_ms *ms, int i);
int		ft_execct(t_ms *ms, int i, int j);
int		ft_open_pipes(t_ms *ms, int i);
void	ft_closefds(t_ms *ms, int i);
void	ft_closepipes(t_ms *ms, int i);
void	ft_heredoc(t_ms *ms, int i, int j);
int		ft_dup(t_ms *ms, int i, int j);
int		ft_exec(t_ms *ms, char **cmd);
char	*ft_pathjoin(char *path, char *cmd);
int		ft_newin(t_ms *ms, int i, int j);
int		ft_newout(t_ms *ms, int i, int j);
void	ft_forking_helper(t_ms *ms, int i, int j);

//		ft_expansion.c
char	*ft_expand(t_ms *ms, char *s);

//		ft_lexer.c
t_list	*ft_lexer(t_ms *ms);
void	ft_gettextquote(t_token *token, char **strptr, char quote);
void	ft_getspace(t_token *token, char **strptr);

//		ft_lexer2.c
int		ft_isspace(int c);
int		ft_istoken(int c);
int		ft_isquote(int c);
void	ft_settoken(t_token *token, int type, char *s);
void	ft_gettext(t_token *token, char **strptr);

//		ft_lexer3.c
t_token	*ft_gettoken(char **strptr);

//		ft_minishell_utils.c
void	ft_errorcheck(t_ms *ms);

//		ft_parser.c
int		ft_fillcts(t_ms *ms, int i, int j);
void	ft_updatecsn(t_ms *ms);

//		ft_parser2.c
int		ft_fillctfd(t_ct *ct, char *file, int *r);

//		ft_parser3.c
int		ft_createct(t_ms *ms);
int		ft_parser(t_ms *ms);
int		ft_createcs(t_ms *ms);
void	ft_updatectn(t_ms *ms);

//		ft_parsetext.c
int		ft_jointext(t_ms *ms);
int		ft_expand_strings(t_ms *ms);

//		ft_parsetext2.c
int		ft_expand_strings(t_ms *ms);

//		ft_signal.c
void	ft_newline(int signal);
void	ft_global_sig(int signal);
void	ft_newglobal_sig(int signal);
void	ft_exit_sig(int signal);

//		ft_tokenchecker.c
int		ft_tokenchecker(t_ms *ms);

//		ft_tokenchecker2.c
void	ft_extra_check_test(t_check *check);
void	ft_extra_check(t_list *lst, t_check *check);
void	ft_check_stuff(t_check *check);
void	ft_check_text(t_check *check);

//		ft_wildcard.c
void	ft_update_lst(t_list **lst, char *s, int hidden);
void	ft_delstring(void *ptr);
t_list	*ft_get_dir(int mode);

//		ft_wildcard2.c
int		ft_wild_fits(char *w, char *s);
void	ft_replace_token(t_ms *ms, t_list *lst, t_token *token, t_list *dir);

//		ft_wildcard3.c
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
