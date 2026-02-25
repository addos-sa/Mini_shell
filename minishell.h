/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:42:18 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/16 12:32:00 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

// Colors
# define RED    "\033[0;31m"
# define GREEN  "\033[0;32m"
# define YELLOW "\033[1;33m"
# define BLUE   "\033[0;34m"
# define PINK   "\033[0;35m"
# define NC     "\033[0m"

// Remove ^C terminal
# define ECHOCTL 0001000

typedef struct s_token
{
	char			*word;
	int				in;
	int				out;
	char			*infile;
	char			*outfile;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}	t_env;

typedef struct s_paths
{
	int		i;
	int		j;
	int		slash;
	char	*pwd;
}	t_paths;

typedef struct s_cut
{
	pid_t	*fk;
	int		(*fd1)[2];
	int		cmm_count;
}	t_pipes;

// Remove Current Directory Fix
void	ft_rm_cwd(t_env *env);
int		divide_paths_null(char **paths);
char	**divide_paths(char *pwd);
void	fill_paths(char **paths, t_paths *data);
void	free_paths(char **paths);
int		how_many_slash(char *pwd);

// Signals
void	ft_set_flag(int i);
void	ft_handler_int(int signal);
void	backslash_control(int signal);
void	ft_disable_echoctl(void);
int		ft_get_flag(void);
void	ft_init_signals(void);

// Token_maker Funcs
t_token	*ft_token_maker(char *line, t_env *env);
t_token	*ft_lstnew_token(void *content);
t_token	*ft_lstlast_token(t_token *lst);
void	ft_lstadd_back_token(t_token **lst, t_token *new);
void	free_tokens(t_token **tokens);

// dollar_vars == Enviorement vars ($(HOME) example)
char	*expand_env_var(char *str, t_env *env);
void	expand_env_vars(t_token *tokens, t_env *env);
char	*get_env_value(const char *name, t_env *env);
char	*expand_dollar_build(const char *str,
			int *ii, char **ptrs, t_env *env);
char	*expand_dollar_once(const char *str, t_env *env, int *found);
char	*expand_all_dollars(const char *str, t_env *env);
char	*strip_quotes(char *str);

// Env_maker Funcs
t_env	*ft_env_maker(char **env);
int		ft_search_equal(char *save);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *env);
int		ft_set_env_name(t_env *new, char *env, int length);
int		ft_set_env_data(t_env *new, char *env, int length);
void	free_env(t_env *env);
// Env Utils 1
char	*search_env_data(char *var, t_env *env_cp);
int		already_exist_env_export(t_env *env, t_token *token);
void	env_export(t_env *env);

// Builts_in
int		commands(t_env **env, t_token *token, char **envp);
int		is_a_builtin(t_token *token);
void	built_in(t_env **env, t_token *token);

// Exec_builtsin
int		echo_builtin(t_token *token);
int		pwd_builtin(t_token *token);
int		env_builtin(t_env **env, t_token *token);
int		export_builtin(t_env **env, t_token *token);
int		unset_builtin(t_env **env, t_token *token);
int		cd_builtin(t_env **env, t_token *token);

// Exit_built_in
int		is_exit(t_token **token, t_env **env);

// ft_split_token
char	**ft_split_token(char const *s, char c);
int		is_quote(char c);

// dquotes
int		no_dquote(char *line);
char	*remove_quotes_dquote(char *word);

//////////////////////////////////////////////////

// pars
t_token	*init_tk(void);
t_token	*construction(char **info, t_env *envp, int *i);
t_token	*pars(char **info, t_env *envp);
char	*add_neg(char *neg, char **word);
void	existance(char *info, int f, t_token **token, char *is_needed);
void	error_hand(int p, t_token **token, char *info);
char	*join_and_free(char *s1, char *s2);
char	*add_char_to_str(char *str, char c);
int		process_variable(char *str, int *i, t_env *envp, char **result);
char	*expand_dolar(char *str, t_env *envp);
void	is_there_a_dolar(t_token **token, t_env *envp);
void	infiles_extras(t_token **cmm);
int		those_ones(t_token *token, int c);
void	make_built_in(t_token **token);
int		is_a_builtin_space(t_token *token);

//finding paths
char	*find_path(t_token **token, char **envp, t_env **env);
char	*path_found(char **envp);

//pipex
int		is_there_a_pipe(char *line);
int		is_built_alone(t_token **token);
void	close_all_pipes(int (*fd1)[2], int count);
int		counter_commander(t_token **cmm);
void	free_pipex(t_token **cmm, t_pipes **pipes, char ***envp);
int		count_envp(t_env *envp);
void	pipex_nodes(t_token **cmm, t_env *env);
int		which_open(t_token	*cmm, int which);
void	command(t_token **cmm, char ***envp, t_env **env);
void	picking_doors(t_token *cmm);
void	delete_lst_part(t_token **cmm);
void	print_error(t_token *cmm);
void	is_the_direction(t_token **cmm, char **envp);

// Shavings
void	shavings1_sons(t_token **cmm, char ***envp, t_pipes **pipes,
			t_env **env);
char	**shavings1_nodes_envp(t_env *envp);
void	shavings_shavings_pars(t_token **token, char **info, int c);
void	shavings_pars(t_token **token, char **info, int c, int i);
void	shavings_prepars(t_token **token, char **info, int c);
char	*free_split(char **split);

// Here_doc
void	inside_doc( char *cutter, int fd1[2]);
int		here_doc(t_token *cmm);
int		alone_pipe(char *line);

#endif
