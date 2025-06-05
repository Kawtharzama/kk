#include "../includes/minishell.h"

void execute_commands(t_all *as, t_command *cmd_list, t_envp *env)
{
	int fd[2];
	int prev_fd = -1;
	pid_t pid;
	int status;

	// For dynamic PID storage
	as->child_pids = malloc(8 * sizeof(pid_t));
	if (!as->child_pids)
		exit_program(as, "malloc failed", 1); // ask

	int num_forked_children = 0;
	int max_children_capacity = 8;

	// (void)as;
	t_command *count_list;
	count_list = cmd_list;
	int c = 0;
	while (count_list)
	{
		count_list = count_list->next;
		c++;
	}
}
