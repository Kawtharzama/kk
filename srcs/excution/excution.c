#include "../includes/minishell.h"

int prepare_pipe_and_fork(t_all *as, int fd[2], int has_next)
{
	if (has_next && pipe(fd) == -1)
	{
		exit_fork(as, "pipe"); // ask
	}
	pid_t pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		exit_fork(as, "fork"); // ask
	}
	return pid;
}

void redirect_io(t_all *as, t_command *cmd, int prev_fd, int fd[2]) // return int
{
	if (cmd->heredoc) // merge
	{
		int fd_heredoc = open("/tmp/minishell_heredoc_tmp.txt", O_RDONLY);
		if (fd_heredoc == -1)
		{
			exit_fork(as, "open heredoc2"); // ask
		}
		dup2(fd_heredoc, STDIN_FILENO);
		close(fd_heredoc);
		// TODO: remove in perent
	}
	else if (cmd->infile)
	{
		int fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in == -1)
		{
			// close(fd[0]) ask tasnim to close 1 or 2?
			exit_fork(as, "infile"); // ask
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);

	if (cmd->outfile)
	{
		int fd_out = open(cmd->outfile, cmd->append ? O_WRONLY | O_CREAT | O_APPEND : O_WRONLY | O_CREAT | O_TRUNC, 0644);


		if (fd_out == -1)
		{
			// close(fd[1]) ask tasnim to close 1 or 2?
			exit_fork(as, "outfile"); // ask
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		//     if (dup2(fd_in, STDIN_FILENO) == -1) //ask
		// exit_fork(as, "dup2 infile");
	}
	else if (cmd->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
}

char *heredoc_cmd(t_all *as, char *del, int n) // merge
{
	(void)as;
	int fd = open("/tmp/minishell_heredoc_tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644); // open a file
	if (fd == -1)
	{

		exit_program(as, "open heredoc", 1); // ask//do not exit
		// check this 1
	}
	while (1)
	{

		char *line = readline("> ");
		if (!line)
			break;
		int len = ft_strlen(line);
		if (len == n && (ft_strncmp(line, del, n) == 0))
		{
			free(line);
			break;
		}
		write(fd, line, len);
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return ft_strdup("/tmp/minishell_heredoc_tmp.txt");
}
void child_process_logic(t_all *as, t_command *cmd, t_envp *env, int prev_fd, int fd[2])
{
	redirect_io(as, cmd, prev_fd, fd);

	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}

	if (built_in(cmd))
	{
		execute_built_ins(cmd, env);
		exit_forkk(as,NULL,0);
		
	}
	else
	{

		if(!cmd->args)
			exit_forkk(as,NULL,0);
		char *path;

		if (ft_strchr(cmd->args[0], '/'))
			path = cmd->args[0];
		else
			path = find_path(env, cmd->args[0]);
			
			
	

		if (!path)
		{

			// close(fd[]); 1 or 0 ask tasnim
			exit_forkk(as, "command not found", 127); // ask
		}
		restore_signals();
		free(cmd->args[0]);
		cmd->args[0] = ft_strdup(path);  //ask
		execve(path, cmd->args, env->tmp_envp);

		exit_fork(as, "execv"); // ask
	// ask
	}
}

void parent_process_cleanup(t_command *cmd, int *prev_fd, int fd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next != NULL)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
}

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

	while (cmd_list)
	{
		// TODO if it is 1 cmd excute here , multiole in child
		if (cmd_list->executable == 1)
		{
			if (built_in(cmd_list) && c == 1 && (!cmd_list->infile && !cmd_list->outfile && !cmd_list->heredoc)) // add the
			{																									 // shall i add heredoc? ask

				execute_built_ins(cmd_list, env);
			}
			else
			{

				pid = prepare_pipe_and_fork(as, fd, cmd_list->next != NULL);
				if (pid == 0)
					child_process_logic(as, cmd_list, env, prev_fd, fd);
				else
				{
					// Store PID
					if (num_forked_children == max_children_capacity)
					{
						max_children_capacity *= 2;
						pid_t *temp_pids = realloc(as->child_pids, max_children_capacity * sizeof(pid_t)); // forbidden cmd
						if (!temp_pids)
						{
							perror("realloc");
							free(as->child_pids);
							exit(EXIT_FAILURE); // ask program or fork // it is program
						}
						as->child_pids = temp_pids;
					}
					as->child_pids[num_forked_children++] = pid;

					parent_process_cleanup(cmd_list, &prev_fd, fd);
				}
			}
		}
		cmd_list = cmd_list->next;
	}
	// ask shall i add if
	//  for (int i = 0; i < num_forked_children; i++)
	//  {
	//      waitpid(as->child_pids[i], &status, 0);
	//      if (as->child_pids[i] == as->child_pids[num_forked_children - 1])
	//          last_status = status;
	//  }
	//  if (WIFEXITED(last_status))
	//      as->exit_status = WEXITSTATUS(last_status);
	//  else if (WIFSIGNALED(last_status))
	//      as->exit_status = 128 + WTERMSIG(last_status);
	//  ("/tmp/minishell_heredoc_tmp.txt");    ask
	int i = 0;
	while (i < num_forked_children)
	{
		int wpid = waitpid(as->child_pids[i], &status, 0);

		if (wpid == as->child_pids[num_forked_children - 1])
		{
			if (WIFEXITED(status))
				as->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				as->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}

	// for (int i = 0; i < num_forked_children; i++)
	//     waitpid(as->child_pids[i], &status, 0);

	free(as->child_pids);
	as->child_pids = NULL;
}
