#include "../includes/minishell.h"

int prepare_pipe_and_fork(int fd[2], int has_next)
{
    if (has_next && pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);//ask
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);//ask
    }
    return pid;
}

void redirect_io(t_command *cmd, int prev_fd, int fd[2]) //return int
{
    if (cmd->heredoc) //merge
    {
         int fd_heredoc = open("/tmp/minishell_heredoc_tmp.txt", O_RDONLY);
         if (fd_heredoc == -1)
         {
             perror("open heredoc2");
            // as->exit_status = 1;
            exit(EXIT_FAILURE);
        }
        dup2(fd_heredoc, STDIN_FILENO);
        close(fd_heredoc);
        // unlink("/tmp/minishell_heredoc_tmp.txt"); // TODO: remove in perent
    }
    else if (cmd->infile)
    {
        int fd_in = open(cmd->infile, O_RDONLY);
        if (fd_in == -1)
        {
            perror("infile");
            exit(EXIT_FAILURE);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    else if (prev_fd != -1)
        dup2(prev_fd, STDIN_FILENO);

    if (cmd->outfile)
    {
        int fd_out = open(cmd->outfile, cmd->append
                          ? O_WRONLY | O_CREAT | O_APPEND
                          : O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
        {
            perror("outfile");
            exit(EXIT_FAILURE);
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
    else if (cmd->next != NULL)
        dup2(fd[1], STDOUT_FILENO);
}


char *heredoc_cmd(t_all *as, char *del , int n) //merge
{
        int fd = open("/tmp/minishell_heredoc_tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);//open a file
        if (fd == -1)
        {
                perror("open heredoc");
                as->exit_status = 1;
                exit(as->exit_status);//check this 1
        }
        while(1)
        {

                char *line = readline("> ");
                if(!line)
                        break ;
                 int len = ft_strlen(line);
                if(len == n && (ft_strncmp(line, del, n )== 0))     
                {
                        free(line);
                        break;
                }
                write(fd, line, len);
                write(fd,"\n",1);
                free(line);
        }        
        close(fd);
            return ft_strdup("/tmp/minishell_heredoc_tmp.txt"); 
        

}
void child_process_logic(t_command *cmd, t_envp *env, int prev_fd, int fd[2], t_all *as)
{
    redirect_io(cmd, prev_fd, fd);

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
        exit(0);
    }
    else
    {
        char *path = cmd->args[0][0] == '/' ? cmd->args[0] : find_path(env, cmd->args[0]);
        if (!path)
        {

            fprintf(stderr, "%s: command not found\n", cmd->args[0]);
            free_token_cmd(as);
            free_envp(env);
            exit(127);
        }
        restore_signals();
        execve(path, cmd->args, env->tmp_envp);
        perror("execv");

        exit(EXIT_FAILURE);//ask

        free_token_cmd(as);
        free_envp(env);
        exit(EXIT_FAILURE);

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
    pid_t *child_pids = malloc(8 * sizeof(pid_t));
    int num_forked_children = 0;
    int max_children_capacity = 8;

    // (void)as;
    t_command *count_list;
    count_list = cmd_list;
    int c =0;
    while (count_list)
    {
        count_list = count_list -> next;
        c++;
    }
     
    while (cmd_list)
    {
          //TODO if it is 1 cmd excute here , multiole in child
        if(cmd_list->executable == 1)
        {
            if (built_in(cmd_list) && c == 1) //add the
            {
                execute_built_ins(cmd_list, env);
            }
            else
            {
                pid = prepare_pipe_and_fork(fd, cmd_list->next != NULL);
                if (pid == 0)
                    child_process_logic(cmd_list, env, prev_fd, fd, as);
                else
                {
                    // Store PID
                    if (num_forked_children == max_children_capacity)
                    {
                        max_children_capacity *= 2;
                        pid_t *temp_pids = realloc(child_pids, max_children_capacity * sizeof(pid_t));
                        if (!temp_pids)
                        {
                            perror("realloc");
                            free(child_pids);
                            exit(EXIT_FAILURE);//ask
                        }
                        child_pids = temp_pids;
                    }
                    child_pids[num_forked_children++] = pid;

                    parent_process_cleanup(cmd_list, &prev_fd, fd);
                }
            }
           
        }
         cmd_list = cmd_list->next;
    }

    unlink("/tmp/minishell_heredoc_tmp.txt");//ask
    int i =0;
    while(i< num_forked_children)
    {
        waitpid(child_pids[i], &status, 0);
        if(waitpid(-1, &status, 0) == (child_pids[num_forked_children - 1 ]))
        {
            if(WIFEXITED(status))
             {
                as->exit_status = WEXITSTATUS(status);
             }
            else if (WIFSIGNALED(status)) {
                as->exit_status = 128 + WTERMSIG(status);  
         }
    }
        i++;
    }                                                                                                                                                                                           
    // for (int i = 0; i < num_forked_children; i++)
    //     waitpid(child_pids[i], &status, 0);
     

    free(child_pids);
}
