#include "../includes/minishell.h"

void print_commands(t_command *cmd_list)
{
    int i;
    int cmd_num = 1;
    t_command *cmd = cmd_list;

    while (cmd)
    {
        printf("=== Command %d ===\n", cmd_num);

        // Print arguments
        if (cmd->args)
        {
            printf("Arguments:\n");
            for (i = 0; cmd->args[i]; i++)
                printf("  [%d]: %s\n", i, cmd->args[i]);
        }
        else
        {
            printf("Arguments: None\n");
        }

        // Print infile
        if (cmd->infile)
            printf("Infile: %s\n", cmd->infile);
        else
            printf("Infile: None\n");

        // Print outfile
        if (cmd->outfile)
            printf("Outfile: %s (append: %s)\n", cmd->outfile, cmd->append ? "yes" : "no");
        else
            printf("Outfile: None\n");
        if (cmd->heredoc)
            printf("Herdoc : %d",cmd->heredoc);    


        printf("\n");
        cmd = cmd->next;
        cmd_num++;
    }
}



int main(int argv, char** argc, char** envp)
{
    (void)argv;
    (void)argc;
    (void)envp;
    char *input;
    char *path;
    t_all *as;
    as = NULL;
  
    as = init_strcuts(as);
    if(!as) // is there a need??

    {

        exit_program(as,"error in init all structs strcut",1);
    }
    copy_envp(envp, as);//check with export
 
	// print_envp(as->cp_envp);
    // char *path = ft_getenv("PATH",as->cp_envp);
    while(1)
    {
        path = cur_dir(as); 
        setup_signals();
        input = readline(path); //is it correct?
        free(path);
        if (input == NULL)
		{
			write(1, "exit\n", 5);
			break;
		}
        
        ignore_signals();
        
        add_history(input);
        // char *x= expand_variables(input,as);//move to before execve
        // printf("%s",x);
        toknize(input,as);
        

       
        print_list(as->token);
       
        


        free(input);
        
        free_token_cmd(as);// clean token & cmds
       
    }
    int g_exit = as->exit_status;//??
    clean(as); //clean all
    
    return (g_exit);
}