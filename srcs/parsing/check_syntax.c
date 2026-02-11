
#include "../../include/minishell.h"

/* affiche un msg derreuur de syntax */
void print_syntax_error(char *token, t_exec_data *data)
{
	ft_putstr_fd("mimishell : syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
	data->status = 2;
}

/* on check les erreur de syntax non valide des pipe */
int	check_pipe_syntax(t_token *token, t_exec_data *data)
{
	if (token->type == TOKEN_PIPE)
	{
		print_syntax_error("|", data);
		return (-1);
	}
	while (token)
	{
		if (token->type == TOKEN_PIPE)
		{
			if (token->next == NULL)
			{
				print_syntax_error("newline", data);
				return (-1);
			}
			if (token->next->type == TOKEN_PIPE)
			{
				print_syntax_error("|", data);
				return (-1);
			}
		}
		token = token->next;
	}
	return (0);
}

/* affiche lerreur selon le type de token apres redir */
void	print_redir_error(t_token_type type, t_exec_data *data)
{
	if (type == TOKEN_PIPE)
		print_syntax_error("|", data);
	else if (type == TOKEN_AND)
		print_syntax_error("&&", data);
	else if (type == TOKEN_OR)
		print_syntax_error("||", data);
	else if (type == TOKEN_REDIR_IN)
		print_syntax_error("<", data);
	else if (type == TOKEN_REDIR_OUT)
		print_syntax_error(">", data);
	else if (type == TOKEN_APPEND)
		print_syntax_error(">>", data);
	else if (type == TOKEN_HEREDOC)
		print_syntax_error("<<", data);
}

/* on check les erreur de syntax nn valide des redir */
int	check_redir_syntax(t_token *token, t_exec_data *data)
{
	while (token)
	{
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		{
			if (token->next == NULL)
			{
				print_syntax_error("newline", data);
				return (-1);
			}
			if (token->next->type != TOKEN_WORD)
			{
				print_redir_error(token->next->type, data);
				return (-1);
			}
		}
		token = token->next;
	}
	return (0);
}
