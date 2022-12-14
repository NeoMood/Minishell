/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:53:56 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/06 15:32:40 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef enum e_def{
	PIP,
	VAR,
	SQUOTE,
	DQUOTE,
	RINPUT,
	ROUTPUT,
	DINPUT,
	DOUTPUT,
	WORD,
	SP
}	t_def;
typedef enum e_type{
	COMMAND,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC
}	t_type;
typedef struct s_env{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_free{
	void			*ptr;
	struct s_free	*next;
}t_free;

typedef struct s_global{
	t_free	*trash;
	int		g_sig;
	int		g_exit;
	int		g_check;
}t_global;

t_global	g_mode;

typedef struct s_exp{
	char			*key;
	char			*value;
	struct s_exp	*next;
}t_exp;

typedef struct s_tk{
	char		*input;
	int			token;
	struct s_tk	*next;
}t_tk;

typedef struct s_args{
	char			**arg;
	t_type			type;
	struct s_args	*next;
}t_args;

typedef struct s_vars{
	char	*path;
	int		fd[2];
	int		num;
	int		i;
	char	**cmd;
}t_vars;

typedef struct s_file{
	int				fd;
	struct s_file	*next;
	struct s_file	*prev;
}t_file;

typedef struct s_fds{
	t_file	*out_f;
	t_file	*in_f;
	t_file	*app_f;
	t_file	*here_f;
	int		new_out;
	int		new_in;
}t_fds;

typedef struct s_exenv{
	t_env		*env;
	t_exp		*exp;
	t_args		*args;
	char		**envar;
	char		*line;
	t_env		*head;
	char		**new_env;
}t_exenv;

// UTILS LIBFT
int		event(void);
char	*ft_substr(char const *s, int start, int len);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_join2darray(char **tmp, char **temp);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlcpy_v2(char *dst, const char *src);
char	*ft_strjoin_v2(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
int		ft_isalpha(int c);
char	*ft_itoa(int n);
int		ft_isdigit(int c);

// LINKED LIST OF PARSING
t_tk	*ft_input(char *data, int token);
void	ft_freelist(t_tk *list);
t_tk	*ft_findlast(t_tk *lst);
void	ft_addtolist(t_tk **list, t_tk *lst);
void	printlist(t_tk *list);

// MINISHELL UTILS
char	**ft_table(char **tmp2, char *tmp1);
void	free_twodarray(char **str);
void	ft_extraspace(char *line);
int		ft_isspace(char c);
void	ft_free(char **tmp);

// LEXER
t_tk	*ft_token_space(t_tk *list);
t_tk	*ft_lexer(char *line);

// ENV AND ITS UTILS
t_env	*ft_createcell(char *key, char	*value);
t_exp	*ft_createcell2(char *key, char	*value);
void	ft_addbacknode(t_env **env, t_env *nv);
void	ft_addbacknode2(t_exp **exp, t_exp *nv);
char	*ft_getvalue(t_env *env, char *key);
t_exp	*ft_last_node2(t_exp *nv);
t_env	*ft_last_node(t_env	*nv);
t_env	*ft_getenv(char **envp);
void	printenv(t_env *ev);
char	**our_env(char **env);

// SIGNALS
void	ft_handler(int sig);
void	ft_hide_c(void);
void	ft_show_c(void);

// LEXER UTILS
int		ft_checkdquotes(int i, char *line, t_tk **list);
int		ft_checksquotes(int i, char *line, t_tk **list);
int		ft_checkdollar(int i, char *line, t_tk **list);
int		ft_wildcard(char *line, int i, t_tk **list);
int		ft_checkrinput(int i, t_tk	**list);
int		ft_checkdoutput(int i, t_tk **list);
int		ft_checkroutput(int i, t_tk **list);
int		ft_checkdinput(int i, t_tk **list);
int		ft_checkspace(int i, t_tk **list);
int		ft_checkpip(int i, t_tk **list);
int		ft_getword(char *line, int i);
int		ft_delimiter(char c);

// EXPAND UTILS
t_tk	*ft_expand(t_tk *list, t_env *ev);

// PRASE AND PARSE UTILS
t_tk	*ft_initialparse(t_tk *list);

// SYNYAX ERROR
int		ft_syntaxredirection(t_tk *list);
int		ft_checksyntaxpip(t_tk *list);
int		ft_checkfirst(t_tk *list);
int		ft_fullcheck(t_tk *list);

// PRE PARSING
t_args	*ft_joiner(t_args *parse);
t_args	*ft_merge(t_args *parse);

// PARSING
void	ft_collectredirection(t_tk **list, t_args **redirection);
void	ft_collectheredoc(t_tk **list, t_args **herdoc);
void	ft_collectword(t_tk **list, t_args **word);
t_args	*ft_finalparsing(char *line, char **env);
void	ft_collectpip(t_tk **list, t_args **pip);
void	ft_collectinput(t_tk **list, t_args **redirection);

// MINISHELL UTILS
void	ft_fdadd_back(t_file **lst, t_file *nv);
t_file	*ft_lstnewfd(int fd);
t_file	*ft_lstlastfd(t_file *lst);
void	ft_addbackarg(t_args **pars, t_args *nv);
t_args	*ft_args_node(char **ar, t_type type);
t_args	*ft_initialparsing(t_tk *list);
void	ft_printarg(t_args *args);
t_args	*ft_last_arg(t_args *lst);

// Exuction PART
int		ft_redirection(t_fds	*fds, t_exenv exenv);
void	init_fds(t_fds **fds);
int		ft_openout(t_args *nw);
int		ft_openin(t_args *nw);
int		ft_append(t_args *nw);

// COMMANDS
char	*char_checker(t_env *envar, char *arg);
void	ft_builtins(t_exenv exenv, t_fds	*fds);
char	*expansion(t_env *envar, char *str);

// NEO COMMANDS
void	ft_cd(t_exenv exenv);
void	ft_pwd(void);
void	ft_env(t_exenv exenv);
void	ft_echo(char **data);
void	ft_export(t_exenv exenv);
t_exp	*env_to_exp(t_env *env);
void	sort_exp(t_exp **exp);
void	exp_print(t_exp **exp);
void	ft_unset(t_exenv exenv);
t_exp	*ft_getexp(char **env);
char	*get_path(t_env	*env, char **cmd);
void	parse_cmd(t_exenv exenv);
void	parse_multicmd(t_exenv exenv, t_fds	*fds);
int		get_error(char *s);
char	*get_path2(t_env	*env, char **cmd);
void	get_filerror(char **cmd);
char	**get_cmd(char **cmd);
int		cmd_num(t_args *args);
void	ft_lstadd_back(t_exp **lst, t_exp *nv);
int		ft_exit(t_exenv exenv);
char	**get_newenv(t_env	*env);
int		list_size(t_env	*env);
int		check_key(char *key);
void	processing_firstcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds);
void	processing_mdlcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds);
void	processing_lastcmd(t_vars *vars, t_exenv exenv, int *fd, t_fds	*fds);
int		get_index(const char *s, int c);
char	*get_key(const char *s, int c);
int		if_exists(t_exp	*exp, char *key);
int		if_exists2(t_env	*env, char *key);
int		check_plequal(char *arg);
t_exp	*ft_lstlast(t_exp *lst);
void	exp_print(t_exp **exp);
t_exp	*ft_getexp(char **env);
int		check_key(char *key);
void	sort_util(char	*tmp, char	*tmpv, t_exp	**i, t_exp	**j);
void	sort_exp(t_exp **exp);
void	update_value(t_exp	*exp, char *key, char *val);
void	update_envalue(t_env	*env, char *key, char *val);
void	add_value(t_exp	*exp, char *key, char *val);
void	sort_n_print(t_exenv *exenv);
void	out_check(t_fds	**fds);
int		check_redirections2(t_exenv *exenv, t_fds	**fds);
void	check_redirections(t_exenv *exenv, t_fds	**fds);
void	check_command(t_exenv *exenv, t_fds	**fds);
void	ft_error(t_exenv exenv);
void	ft_handlelong(t_exenv exenv);
void	ft_negativenum(int j, t_exenv exenv);
void	ft_postifnum(int j, t_exenv exenv);

// MAIN UTILS
void	ft_execution(t_exenv exenv, t_fds *fds);
int		ft_check_builtins(t_exenv exenv);
t_args	*ft_corrector(t_args *parse);
int		check_pipe(t_args *args);
void	my_exit(void);

// free
void	ft_freegarbe(t_free *list);
void	ft_addbackthegarbe(t_free **lst, t_free *nv);
// void	*ft_malloc(size_t allocation);
t_free	*ft_lstgarbage(t_free *lst);
t_free	*ft_newgarbage(void *ptr);

#endif