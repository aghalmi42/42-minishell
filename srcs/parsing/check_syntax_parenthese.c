
#include "../../include/minishell.h"

int	handle_close_paren(int count, int content, t_exec_data *data)
{
    if (count == 0)
	{
        if (!content)
		{
            print_syntax_error(")", data);
			return (0);
		}
		return (1);
	}
	return (-1);
}

/* trv la parenthese fermante et verif du contenu */
int	check_content_enter_paren(t_token *left_paren, t_exec_data *data)
{
	int		count;
	t_token	*current;
	int		content;
	int		result;

	count = 1;
	current = left_paren->next;
	content = 0;
	while (current && count > 0)
	{
		if (current->type == TOKEN_LEFT_PAREN)
			count++;
		else if (current->type == TOKEN_RIGHT_PAREN)
		{
			count--;
			result = handle_close_paren(count, content, data);
			if (result != -1)
				return (result);
		}
		else
			content = 1;
		current = current->next;
	}
	print_syntax_error("newline", data);
	return (0);
}

int	process_paren_token(t_token *current, int *count, t_exec_data *data)
{
    if (current->type == TOKEN_LEFT_PAREN)
	{
        (*count)++;
		if (!check_content_enter_paren(current, data))
        return (0);
	}
	else if (current->type == TOKEN_RIGHT_PAREN)
	{
        (*count)--;
		if (*count < 0)
		{
            print_syntax_error(")", data);
			return (0);
		}
	}
	return (1);
}

/* verifife les parenthese */
int	check_parenthese_syntax(t_token *token, t_exec_data *data)
{
	int		count;
	t_token	*current;

	count = 0;
	current = token;
	while (current)
	{
		if (!process_paren_token(current, &count, data))
			return (0);
		current = current->next;
	}
	if (count != 0)
	{
		print_syntax_error("newline", data);
		return (0);
	}
	return (1);
}
