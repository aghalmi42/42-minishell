
#include "../../include/minishell.h"

/* gere les && et les || */
int manage_logical(char *line, int *i, t_token **up)
{
    t_token *token;

    if (line[*i] == '&' && line[*i + 1] == '&')
    {
        token = new_token(TOKEN_AND, NULL);
        add_token(up, token);
        (*i) += 2;
        return (1);
    }
    if (line[*i] == '|' && line[*i + 1] == '|')
    {
        token = new_token(TOKEN_OR, NULL);
        add_token(up, token);
        (*i) += 2;
        return (1);
    }
    return (0);
}
