/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:14:38 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/01 14:31:44 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include "../../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
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
int					check_pipe_syntax(t_token *token);
int					check_redir_syntax(t_token *token);
t_token				*split_token(t_token *token, t_token *split);
t_node				*parsing_cmd(t_token *token);
t_node				*parsing_pipe(t_token *token, t_token *pipe_token);
t_node				*parsing_redir(t_token *token, t_token *redir_token);
t_token 			*search_logical(t_token *token);
t_node 				*parsing_pipe_prio(t_token *token);
t_node 				*parsing_and(t_token *token, t_token *and_token);
t_node 				*parsing_or(t_token *token, t_token *or_token);
t_node				*parsing(t_token *token);

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