
#include "../../include/minishell.h"

/* pour gerer les parenthesse */
int  manage_parenthese(char *line, int *i, t_token **up)
{
    t_token *token;

    if (line[*i] == '(')
    {
        token = new_token(TOKEN_LEFT_PAREN, NULL);
        add_token(up, token);
        (*i)++;
        return (1);
    }
    else if (line[*i] == ')')
    {
        token = new_token(TOKEN_RIGHT_PAREN, NULL);
        add_token(up, token);
        (*i)++;
        return (1);
    }
    return (0);
}
