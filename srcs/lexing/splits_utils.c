#include "../includes/minishell.h"

void free_exit_status(t_all *as)
{
	
		free_token_cmd(as);

		write(2,"Syntax_error\n",13);
		
	
}

int toknize(char* input, t_all *as) //change to void
{
    int i;
	
	i = split_input(as, input, &as->token, as->tmp);
	if(i == -1)
	{
		return(free_exit_status(as),1);
		
	}

	expand_var(as, as->token, as->cp_envp);
	// if(i == -1)
	// 	exit(1);
	// 	// return(free_exit_status(as),1);
	// else
	// 	as->exit_status = 0;	
	// else
	// 	as->exit_status = 0;
	
	
	remove_quotes(as->token);

	print_list(as->token);
	i = split_cmds(as, as->token, &as->cmd);

	// if(i == -1)
	// {
	// 	free_exit_status(as);
	// 	return(1);
	// }
	// else if(i == -2)
	// 	return(free_token_cmd(as),1); edit to be exit
	
	print_commands(as->cmd); //remove   
	execute_commands(as, as->cmd, as->cp_envp);
    return 0; //exit
}

void token_types(t_token *token) 

{
	 while(token)  {
		if (ft_strncmp(token->value, "<<",2) == 0) {
            token->type = HEREDOC;
        }
		else if  ((ft_strncmp(token->value, ">>", 2) == 0) ||
		(ft_strncmp(token->value, ">",1) == 0)||
		 (ft_strncmp(token->value, "<", 1) == 0)) 
		{
			token->type = REDIR;
	        }

		
        else if (ft_strncmp(token->value, "|",1) == 0) {
            token->type = PIPE;
        }
        else {
			
            	token->type = WORD;       

        }
        token = token->next;
       }  
}

int	parameter_token(t_all *as, char *input, int i, t_tmptoken *tmp, t_token **token)
{
	tmp->start = i;
	if (input[i] && input[i + 1] && input[i] == input[i + 1] && input[i + 1] != '|')
		i++;
	tmp->end = i;
	tmp->value = ft_substr(input, tmp->start, (tmp->end - tmp->start
				+ 1)); //free
	if (!tmp->value)
	{
		exit_program(as, "Memory allocation failed", 1);
	}
	if(add_node(token, tmp->value) == -1)
		{return -1;} 
	free(tmp->value);
	tmp->value = NULL;
	return (i);
}

int	is_parameter(char c)
{
	if (c == '|' || c == '>' || c == '<')
	{
		return (1);
	}
	return (0);
}

