#include "../includes/minishell.h"

int toknize(char* input, t_all *as) //change to void
{
    int i = 0;
	i = split_input(input, &as->token, as->tmp);
	if(i == -1)
	{
		free_token_cmd(as);
		as->exit_status = 1; //add int exiyt to be 1;
		return 1;//void
	}
	expand_var(as, as->token, as->cp_envp);
	remove_quotes(as->token);
	
	split_cmds(as, as->token, &as->cmd);
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
		else if  (ft_strncmp(token->value, ">>", 2) == 0 ||(ft_strncmp(token->value, ">",1) == 0) || (ft_strncmp(token->value, "<", 1) == 0) ) {
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

int	parameter_token(char *input, int i, t_tmptoken *tmp, t_token **token)
{
	tmp->start = i;
	if (input[i + 1] && input[i] == input[i + 1] && input[i + 1] != '|')
		i++;
	tmp->end = i;
	tmp->value = ft_substr(input, tmp->start, (tmp->end - tmp->start
				+ 1)); //free
	if (!tmp->value)
	{
		printf("Memory allocation failed for tmptoken.value\n");
		return (-1);
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

int	str(char *input, int i, t_tmptoken *tmp, t_token **token)
{
	tmp->start = i;
	int flag ;

	flag = 0;
	while (input[i] && input[i] !=' ' && !is_parameter(input[i]))
		
	{
		if (input[i] == '"' || input[i] == '\'')
		{
		    i = closing_qoutes(input,i);
			if(i == -1)
			{
				return -1;
			}
			flag = 1;
		}
		i++;
		if(flag == 1)
			break;
	}
	tmp->end = i;
	tmp->value = ft_substr(input, tmp->start, (tmp->end - tmp->start));
	if (!tmp->value)
	{
		printf("Memory allocation failed for token.value\n");
		return (-1);
	}
	if(add_node(token, tmp->value) == -1)
		{return -1;} 
	free(tmp->value);
	tmp->value = NULL;
	return (i - 1);
}