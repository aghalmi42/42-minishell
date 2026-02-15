
#include "../../include/minishell.h"

/* cherche first pareent ouvrante*/
t_token *search_parenthese(t_token *token)
{
    while(token)
    {
        if (token->type == TOKEN_LEFT_PAREN)
            return (token);
        token = token->next;
    }
    return (NULL);
}

/* trv la bonne parent fermante */
t_token *find_match_right_paren(t_token *token)
{
    int count;

    count = 1;
    token = token->next;
    while(token && count > 0)
    {
        if (token->type == TOKEN_LEFT_PAREN)
            count++;
        else if (token->type == TOKEN_RIGHT_PAREN)
            count--;
        if (count == 0)
            return (token);
        token = token->next;
    }
    return (NULL);
}

/* copie les token entre les 2 paren dasns uun new lst */
t_token	*copy_token_enter(t_token *start, t_token *end)
{
	t_token	*new_head;
	t_token	*new_current;
	t_token	*current;
	t_token	*copy;

	new_head = NULL;
	new_current = NULL;
	current = start;
	while (current && current != end)
	{
		copy = new_token(current->type, current->value);
		if (!copy)
			return (NULL);
		if (!new_head)
			new_head = copy;
		else
			new_current->next = copy;
		new_current = copy;
		current = current->next;
	}
	return (new_head);
}

/* sert a parser uun subsheell */
t_node *parsing_subshell(t_token *token, t_exec_data *data)
{
    t_node *node;
    t_token *left_paren;
    t_token *right_paren;
    t_token *in_token;

    left_paren = token;
    if (left_paren->type != TOKEN_LEFT_PAREN)
        return (NULL);
    right_paren = find_match_right_paren(left_paren);
    if (!right_paren)
        return (NULL);
    in_token = copy_token_enter(left_paren->next, right_paren);
    node = new_node(NODE_SUBSHELL);
    if (!node)
        return (NULL);
    node->left = parsing_no_check(in_token, data);
    // if (right_paren->next)
    //     node->right = parsing_no_check(right_paren->next, data);
    // else
    node->right = NULL;
    return (node);
}
