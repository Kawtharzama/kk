#include "../includes/minishell.h"

int find_closing_quote(char *input, int i, int flag, char quote_type)
{
    while (input[i])
    {
       if ((input[i] == '"' || input[i] == '\'') && flag == 0)
		{
			quote_type = input[i];
			flag = 1;
          
		}
        else if(input[i] == quote_type && flag == 1)
		{ 
			flag = 0;
			if (input[i + 1] && input[i + 1] != ' ' && !is_parameter(input[i + 1]))
				continue;
			else
				break;
		}
        else if(input[i+1] && flag == 0 && (input[i+1] == ' ' || is_parameter(input[i+ 1])))
    		break;
            i++;     
    }
    if (flag  == 1)
            return -1; //??
        
    return i;
}

int closing_qoutes(char *input, int i)
{
	char quote_type;
	int flag ;

    flag = 1; //inside qoute
    quote_type = input[i];
    i++;
    i = find_closing_quote(input, i, flag, quote_type);
   return i;
}

int	handle_quotes(char *input, int i, t_tmptoken *tmp, t_token **token)
{
    
	tmp->start = i;
	i = closing_qoutes(input,i);
	if (i == -1)
    {
		return (-1); }
	
	tmp->end = i;
	tmp->value = ft_substr(input, tmp->start, (tmp->end - tmp->start
				+ 1));
	if (!tmp->value)
	{
		perror("Memory allocation failed for token.value\n");
		return (-1);
	}
	if(add_node(token, tmp->value) == -1)
	{return -1;} 
	free(tmp->value);
	tmp->value = NULL;
	return (i);
}

// void replace_qoutes(t_token *token, int i, int j, int q)
// {
// 	char c;

//         while (token->value[i] != '\0')
//         {
//             if (q == 0 && (token->value[i] == '"' || token->value[i] == '\''))
//             {
//                 q = 1;
//                 c = token->value[i++];
//                 while (token->value[i] != '\0' && token->value[i] != c)
//                 {
//                     token->value[j++] = token->value[i++];
//                 }
//                 if (token->value[i] == c) i++;
//                 q = 0;
//             }
//             else
//                 token->value[j++] = token->value[i++];
            
//         }
//         token->value[j] = '\0'; 
//     }

// void remove_quotes(t_token *token)
// {
//     int i;
// 	int j;
// 	int q;
    
// 	while (token != NULL)
//     {
//         if (token->value == NULL || token->value[0] == '\0')
//         {
//             token = token->next;
//             continue;
//         }

//         i = 0;
//         j = 0;
//         q = 0;
// 		if (token->type == WORD)
// 			replace_qoutes(token, i, j, q);
// 		token = token->next;


// 	}	
		
// }
 void replace_qoutes(t_token *token, int i, int j, int q)
{
   
    char c;

    if (!token || !token->value)
        return;

    while (token->value[i])
    {
        if (q == 0 && (token->value[i] == '"' || token->value[i] == '\''))
        {
            q = 1;
            c = token->value[i++];
            while (token->value[i] && token->value[i] != c)
                token->value[j++] = token->value[i++];
            if (token->value[i] == c)
                i++;
            q = 0;
        }
        else
            token->value[j++] = token->value[i++];
    }
    token->value[j] = '\0';
}
void remove_quotes(t_token *token)
{
    while (token)
    {
        if (token->value && token->value[0] && token->type == WORD)
            replace_qoutes(token, 0, 0, 0);
        token = token->next;
    }
}



