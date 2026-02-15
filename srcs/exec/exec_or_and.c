
#include "../../include/minishell.h"

void	exec_and(t_node *node, t_exec_data *data)
{
	exec_main(node->left, data);
	if (data->status == 0)
		exec_main(node->right, data);
}

void	exec_or(t_node *node, t_exec_data *data)
{
	exec_main(node->left, data);
	if (data->status != 0)
		exec_main(node->right, data);
}
