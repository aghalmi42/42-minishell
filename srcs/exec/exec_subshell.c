
#include "../../include/minishell.h"

/* exec un suubshell dans uun process enfant */
void exec_subshell(t_node *node, t_exec_data *data)
{
    pid_t pid;
    int status;

    if (!node || !node->left)
    {
        data->status = 0;
        return ;
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        data->status = 1;
        return ;
    }
    if (pid == 0)
    {
        set_signal_actions_default();
        data->is_fork = 1;
        exec_main(node->left, data);
        exit(data->status);
    }
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
        data->status = 128 + WTERMSIG(status);
    else
        data->status = WEXITSTATUS(status);
    set_signal_actions();
    if (node->right)
        exec_main(node->right, data);
}
