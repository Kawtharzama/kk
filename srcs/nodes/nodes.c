#include "../includes/minishell.h"

t_token	*find_last_node(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next != NULL)
	{
		token = token->next;
	}
	return (token);
}

int	add_node(t_token **token, char *input)
{
	t_token	*node;
	t_token	*last_node;

	if (!input)
		return -1;
	node = malloc(sizeof(t_token)); // free 
	if (!node)
		return -1; //what shall it return
	node->value = ft_strdup(input);  //free
	if (!node->value)
		return -1;
	node->next = NULL;
	if (*token == NULL)
		*token = node;
	else
	{
		last_node = find_last_node(*token);
		last_node->next = node;
		node->prev = last_node;
	}
	return 0;
}