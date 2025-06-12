/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_token *head)
{
	t_token	*current;
	int		i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
}

int	split_input(t_all *as, char *input, t_token **token, t_tmptoken *tmp)
{
	int	i;

	*token = NULL;
	i = 0;
	init_token(tmp);
	while (input[i])
	{
		tmp->start = i;
		if (input[i] == '"' || input[i] == '\'')
			i = handle_quotes(as, input, i, tmp);
		else if (input[i] == ' ')
			;
		else if (is_parameter(input[i]))
			i = parameter_token(as, input, i, tmp);
		else
			i = str(as, input, i, tmp);
		if (i == -1)
			return (-1);
		if (!input[i])
			break ;
		i++;
	}
	token_types(*token);
	return (i);
}

int	scan_token(char *input, int i, t_tmptoken *tmp)
{
	int	flag;

	tmp->start = i;
	flag = 0;
	while (input[i] && input[i] != ' ' && !is_parameter(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i = closing_qoutes(input, i);
			if (i == -1)
				return (-1);
			flag = 1;
		}
		i++;
		if (flag == 1)
			break ;
	}
	tmp->end = i;
	return (i);
}

int	str(t_all *as, char *input, int i, t_tmptoken *tmp)
{
	int	end;

	end = scan_token(input, i, tmp);
	if (end == -1)
		return (-1);
	tmp->value = ft_substr(input, tmp->start, tmp->end - tmp->start);
	if (!tmp->value)
		exit_program(as, "Memory allocation failed", 1);
	if (add_node(&as->token, tmp->value) == -1)
		exit_program(as, "Memory allocation failed", 1);
	free(tmp->value);
	tmp->value = NULL;
	return (end - 1);
}
