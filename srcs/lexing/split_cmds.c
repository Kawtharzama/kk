#include "../includes/minishell.h"

t_command *new_command(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->next = NULL;
    cmd->heredoc = 0;
    cmd->executable = 1;
    return cmd;
}


char **add_arg(char **args, char *value)
//appends a new argument string to the end of the args array (resizing as needed)
{
        int count; //to count amount of args
        int i;

        i = 0;
        count = 0;
        while (args && args[count])
                count++;

        char **new_args = malloc(sizeof(char *) * (count + 2)); //allocates one more for the new arg and NULL
        if (!new_args)
                return NULL;

        while (i < count)
        // copy existing args to new array
                {new_args[i] = args[i];
                        i++;}
        new_args[count] = ft_strdup(value); //adds the new arg to the end
        new_args[count + 1] = NULL;

        if (args)
                free(args); // reallocated, old pointer is no longer used
        //frees the old args array but not the strings inside it
        return new_args;
}

void append_command(t_command **cmd_list, t_command *new_cmd)
//appends a new command to the end of the command list
{
        if (!*cmd_list)
        // if the list is empty, set the new command as the head
        {
                *cmd_list = new_cmd;
                return;
        }

        t_command *tmp = *cmd_list; //start from the head
        while (tmp->next)
        //walk through the list until the last command
                tmp = tmp->next;

        tmp->next = new_cmd; // link the new command to the end of the list
}

void split_cmds(t_all *as, t_token *token, t_command **cmd_list)
//splits the token list into a command list
{
         *cmd_list = NULL; //starts with an empty command list
        t_command *current_cmd = new_command();
        (void)as;

        while (token)
        //iterate through the token list
        {
                if (token->type == WORD)
                {
                        current_cmd->args = add_arg(current_cmd->args, token->value);
                }
                else if (token->type == HEREDOC)
                {
                        if (!token->next || token->next->type != WORD) //what to add
                        {
                                printf("Syntax error: expected filename after redirection\n");
                                return ; //free first

                        }
                        // current_cmd->args = add_arg(current_cmd->args, token->value);
                        current_cmd->heredoc = 1;
                        int n = ft_strlen(token->next->value);
                        current_cmd->infile  = heredoc_cmd(as, token->next->value, n);
                        token = token->next; //skip del
                        // append_command(cmd_list, current_cmd);
                        //check
                        // current_cmd = new_command(); 
                      
                        
                        

                }
                else if (token->type == REDIR)
                //then next token should be a filename
                {
                        if (!token->next || token->next->type != WORD)
                        {
                                printf("Syntax error: expected filename after redirection\n");
                                // free(current_cmd); //full cleanup function
                                return ;
                        }

                        if (ft_strncmp(token->value, ">", 1) == 0)
                        {
                                if (ft_strncmp(token->value, ">>", 2) == 0)
                                        current_cmd->append = 1;
                                // TODO: not make free for prev outfile
                                // and not check permission for prev files 
                                current_cmd->outfile = ft_strdup(token->next->value);
                        int fd_out = open(current_cmd->outfile, current_cmd->append ? O_WRONLY | O_CREAT | O_APPEND : O_WRONLY | O_CREAT | O_TRUNC, 0644);
                                if (fd_out == -1)
                                {
                                        perror("outfile");
                                        current_cmd->executable = 0;
                                        
                                       
                                }
                                else
                                        close(fd_out);
                                
                        }
                        else if (ft_strncmp(token->value, "<", 1) == 0)
                        {
                                current_cmd->infile = ft_strdup(token->next->value);
                          
                                 int fd_in = open(current_cmd->infile, O_RDONLY);
                                if (fd_in == -1)
                                {
                                        perror("infile");
                                         current_cmd->executable = 0;
                                         
                                        
                                }
                                else
                                        close(fd_in);
                              
                        }

                        token = token->next; // skip filename
                }
                else if (token->type == PIPE)
                //finially, if we hit a pipe, we need to add the current command to the list
                {
                        append_command(cmd_list, current_cmd);
                        current_cmd = new_command();
                }

                token = token->next;
        }

        if (current_cmd->args) // only add if it has something
                append_command(cmd_list, current_cmd);

        return ; 
}
