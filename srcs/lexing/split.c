#include "../includes/minishell.h"

void	print_list(t_token *head)
{
	t_token	*current;
	int		i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		printf("Token[%d] %s, type: %d\n", i, current->value, current->type);
		current = current->next;
		i++;
	}
}




int split_input (t_all *as, char* input,t_token **token, t_tmptoken *tmp)
{
    *token = NULL;
 	int		i;

 	i = 0;
	init_token(tmp);
 	while (input[i])
 	{
 		tmp->start = i;
 		if (input[i] == '"' || input[i] == '\'')
 				i = handle_quotes(as, input, i, tmp, token);
		else if (input[i] == ' ') 
			;
		 else if (is_parameter(input[i]))
 			i = parameter_token(as, input, i, tmp, token);
        else
 			i = str(as, input, i, tmp, token);
 		if (i == -1)
 			{
   				return -1; //syntax error
			} 
		if(!input[i])	
			break;
 	i++;
 	}
	token_types(*token);
    return i;
}
