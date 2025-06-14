/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:12 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/06/12 17:15:13 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int handle_exit_status(t_all *as, t_token *token, int *i)
{
    if (token->value[*i] == '?')
    {
		(*i)++;
        char *env_value = ft_itoa(as->exit_status);
        int start = *i - 1;
    
        int end = *i;
       
        if (expand_variable(token, env_value, start, end) == -1)
            return (-1);
		free (env_value);
    }
    return (1);
}


int	extract_variable(t_all *as, char *value, int *i, char **var)
{
	int	start;
	int	end;

	start = *i;
	if (isdigit(value[*i]))
	{
		(*i)++;
		*var = ft_strdup("");
		if (!*var)
			exit_program(as, "Memory allocation failed", 1);
		return (start);
	}
	while (value[*i] && (isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	end = *i;
	*var = ft_substr(value, start, end - start);
	if (!*var)
	{
		exit_program(as, "Memory allocation failed", 1);
	}
	return (start);
}

char	*join_before_env(t_token *token, char *env_value, int start)
{
	char	*before;
	char	*var_value;
	char	*tmp;

	before = NULL;
	var_value = ft_strdup(env_value);
	// if (*env_value)
	// 	free(env_value);// thaer
	if (!var_value)
		return (NULL);
	if (start > 1)
	{
		before = ft_substr(token->value, 0, start - 1);
		if (!before)
		{
			return (free(var_value), NULL);
		}
		tmp = var_value;
		var_value = ft_strjoin(before, var_value);
		if (!var_value)
			return (free(before), free(tmp), NULL);
		free(before);
		free(tmp);
	}
	return (var_value);
}
