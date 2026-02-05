/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:14:38 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/05 02:18:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <linux/limits.h>

/*typedef enum sert a faire une enumeration pour bien eclaircir le code
avec des nom explicite c comme si on faisait un define
c defini pour le 1er a 1 le 2eme a 2 etc .... */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
}					t_token_type;

/* structure de token en liste chaineer*/
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

/* type de noeud de notre ast */
typedef enum e_node_type
{
	NODE_CMD,
	NODE_REDIR,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
}					t_node_type;

/* struct des noeud de notre ast */
typedef struct s_node
{
	t_node_type		type;
	char			**av;
	int				redir_type;
	char			*redir_file;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

/* structure pour les data de l'exec */
typedef struct s_exec_data
{
	t_list					*envp;
	int						status;
	struct s_here_doc_fd	*head;
	int						is_pipe;
}					t_exec_data;

/* structure pour le env en liste chaines, simplification pour refaire le code après */
typedef struct s_env
{
	char	*key;
	char	*value;
}					t_env;

/* structure pour contenir les fds des potentiels here_doc ouverts */

typedef struct s_here_doc_fd
{
	int						fd_read;
	struct s_here_doc_fd	*next;

}					t_here_doc_fd;

/* fonction du lexical analyzer */
t_token				*new_token(t_token_type type, char *value);
void				add_token(t_token **up, t_token *new);
void				print_token(t_token *token);
void				free_token(t_token *token);
void				skip_all_space(char *line, int *i);
int					manage_pipe(char *line, int *i, t_token **up);
int					manage_input_redirection(char *line, int *i, t_token **up);
int					manage_output_redirection(char *line, int *i, t_token **up);
int					manage_redirection(char *line, int *i, t_token **up);
int					manage_quote(char *line, int *i, char *word, int *j);
int					manage_double_quote(char *line, int *i, char *word, int *j);
int					manage_logical(char *line, int *i, t_token **up);
int					delimiter(char c);
int					construct_word(char *line, int *i, char *word, int *j);
int					extract_word(char *line, int *i, t_token **up);
t_token				*lexical_analyzer(char *line);

/* fonction de parsing */
t_node				*new_node(t_node_type type);
void				free_ast(t_node *node);
int					count_av(t_token *token);
char				**token_tab_av(t_token *token);
void				print_ast(t_node *node, int tmp);
t_token				*search_pipe(t_token *token);
t_token				*search_redir(t_token *token);
void 				print_syntax_error(char *token);
void				print_redir_error(t_token_type type);
int					check_pipe_syntax(t_token *token);
int					check_redir_syntax(t_token *token);
int					logical_start(t_token *token);
int					check_logical_token(t_token *token);
int					check_syntax_logical(t_token *token);
int					check_syntax(t_token *token);
t_token				*split_token(t_token *token, t_token *split);
t_node				*parsing_cmd(t_token *token);
t_node				*parsing_pipe(t_token *token, t_token *pipe_token);
t_node				*parsing_redir(t_token *token, t_token *redir_token);
t_token 			*search_logical(t_token *token);
t_node 				*parsing_pipe_prio(t_token *token);
t_node 				*parsing_and(t_token *token, t_token *and_token);
t_node 				*parsing_or(t_token *token, t_token *or_token);
t_node				*parsing(t_token *token);

/* path_finding */
char				*path_to_find(char *cmd, char **envp);
char				*join_possible_path(char *cmd, char *folder);
void				free_split(char **split);
int					count_env(char **envp);
int					countain_a_slash(char *str);
char				*it_contain_a_slash(char *cmd);
char				*search_possible_path(char **possible_paths, char *cmd);
char				**search_path(t_list *envp);
char				*path_to_find_lst(char *cmd, t_exec_data *data);

/* set l'environnement en liste chainées */

t_list				*envp_to_lst(char **envp);
t_env				*split_env_line(char *str);
void				del_env(void	*content);
void				free_envp(t_exec_data *data);

/* node fd des here_doc , pretraitement des here_doc pour l'exec */

t_here_doc_fd		*here_doc_new(int	content);
t_here_doc_fd		*here_doc_last(t_here_doc_fd *here_doc);
int					add_here_doc_fd(t_here_doc_fd **head, int fd);
int					search_here_doc_to_execute(t_node *ast, t_exec_data *data);
int					create_here_doc_to_execute(char *redir_file, t_exec_data *data);
void				loop_here_doc(char	*limiter, int fd);

/* exec */

void				exec_one_cmd(t_node *node, char **envp);
void				exec_main(t_node *ast, t_exec_data *data);
int					is_a_built_in(char *cmd);
void				exec_built_in(char *cmd, t_exec_data *data, t_node *node);
char				**getenv_to_str(t_list *envp);
char				*envp_value(t_env *content);
int					envp_count(t_list *envp);
void				exec_pipe(t_node *node, t_exec_data *data);
void				exec_cmd(t_node *node, t_exec_data *data);
void				exec_one_cmd_lst(t_node *node, t_exec_data *data);


/* built-in */

void				built_in_env(t_exec_data *data, int export);
void				built_in_export(t_exec_data *data, t_node *node);
int					check_new_key(t_env *env);
void				print_env(t_env *e, int export);
void				built_in_unset(t_exec_data *data, t_node *node);
void				built_in_exit(t_exec_data *data, t_node *node);

/* redirection exec */
void				exec_redirection(t_node *node, t_exec_data *data);
int					open_redir_file(t_node *node);

/* signals */

extern volatile		sig_atomic_t status;
void				set_signal_actions(void);
void				handle_sigint(int	signal);
/* fonction expansion */
int					single_quote(char *str);
int					dollar(char *str);
char				*remove_quote(char *str);
void				copy_char(char *str, int *i, char *result, int *j);
int					to_expand(char *str, int i, int in_quote);
char				*find_env_value(char *var_name, char **env);
char				*extract_var_name(char *str, int *i);
int					copy_to_result(char *src, char *result);
int					manage_variable(char *str, int *i, char *result,
						char **env);
void				manage_exp_quote(char c, int *in_quote, int *i);
int					manage_exit_code(int *i, char *result);
int					manage_pid(int *i, char *result);
void				expand_token(t_token *token, char **env);
void				expand_word(t_token *token, char **env);
void				case_expand(char *str, char *result, int *var, char **env);
char				*expand_value(char *str, char **env);

/* fonction builtin */
int 				builtin_pwd(void);
int 				n_option(char *av);
int 				builtin_echo(char **av);
char 				*search_home_path(char **env);
char 				*search_oldpwd_path(char **env);
char 				*search_cd_path(char **av, char **env);
int 				change_directory(char *path);
int 				builtin_cd(char **av, char **env);
int 				builtin(char *cmd);
int 				exec_builtin(char **av, char **env);
#endif