/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:14:38 by aghalmi           #+#    #+#             */
/*   Updated: 2026/01/10 11:54:13 by aghalmi          ###   ########.fr       */
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

/*typedef enum sert a faire une enumeration pour bien eclaircir le code
avec des nom explicite c comme si on faisait un define
c defini pour le 1er a 1 le 2eme a 2 etc .... */
typedef enum token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

/* fonction du lexical analyzer */
t_token				*new_token(t_token_type type, char *value);
void				add_token(t_token **up, t_token *new);
void				print_token(t_token *token);
void				free_token(t_token *token);
t_token				*lexical_analyzer(char *line);
#endif