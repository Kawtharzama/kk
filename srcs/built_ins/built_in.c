#include "../includes/minishell.h"

int     built_in(t_command *cmd_list)
{
        t_command *cmd = cmd_list;
        int     return_va = 0;
        
        if (!cmd->args)
                return (0);
        if(ft_strncmp(cmd->args[0], "echo", 4) == 0)
                return_va = 1;
        else if(ft_strncmp(cmd->args[0], "cd", 2) == 0)
                return_va = 1;
        else if(ft_strncmp(cmd->args[0], "pwd", 3) == 0)
                return_va = 1;
        else if(ft_strncmp(cmd->args[0], "export", 6) == 0)
                return_va = 1;
        // else if(ft_strncmp(cmd->args[0], "exit", 4) == 0)
        //         return_va = 1;
        else if(ft_strncmp(cmd->args[0], "unset", 5) == 0)
                return_va = 1;
        else if(ft_strncmp(cmd->args[0], "env", 3) == 0)
                return_va = 1;
        return (return_va);
}

void   execute_built_ins(t_command *cmd_list, t_envp *env, t_all *as) //
{
        t_command *cmd = cmd_list;
        (void)env;
        if(cmd)
        {
                if(ft_strncmp(cmd->args[0], "echo", 4) == 0)
                        execute_echo(cmd->args);
                else if(ft_strncmp(cmd->args[0], "cd", 2) == 0)
                        execute_cd(&cmd->args[1], env);
                else if(ft_strncmp(cmd->args[0], "pwd", 3) == 0)
                        execute_pwd(&cmd->args[1]);
                else if(ft_strncmp(cmd->args[0], "export", 6) == 0)
                        execute_export(cmd->args, env);
                // else if(ft_strncmp(cmd->args[0], "exit", 4) == 0)
                //         execute_exit(cmd->args, env);
                else if(ft_strncmp(cmd->args[0], "unset", 5) == 0)
                        execute_unset(cmd->args, env);
                else if(ft_strncmp(cmd->args[0], "env", 3) == 0)
                        execute_env(cmd->args, env);
        }
}
