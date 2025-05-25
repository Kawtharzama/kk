/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
	t_token		*node;
	t_token		*last_node;

	if (!input)
		return (-1);
	node = malloc(sizeof(t_token));
	if (!node)
		return (-1);
	node->prev = NULL;
	node->value = ft_strdup(input);
	if (!node->value)
		return (-1);
	node->next = NULL;
	if (*token == NULL)
		*token = node;
	else
	{
		last_node = find_last_node(*token);
		last_node->next = node;
		node->prev = last_node;
	}
	return (0);
}
