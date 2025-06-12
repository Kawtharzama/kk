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

int	handle_single_quotes(const char *value, int *i, int in_double)
{
	if (value[*i] == '\'' && in_double == 0)
	{
		(*i)++;
		while (value[*i] && value[*i] != '\'')
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

int	toggle_double_quote(int ch, int in_double)
{
	if (ch == '"')
		return (!in_double);
	return (in_double);
}

int	handle_exit_status(t_all *as, t_token *token)
{
	char	*status_str;

	if (!token || !token->value)
		return (0);
	free(token->value);
	status_str = ft_itoa(as->exit_status);
	if (!status_str)
		exit_program(as, "Memory allocation failed", 1);
	token->value = status_str;
	return (1);
}

int	extract_variable(t_all *as, char *value, int *i, char **var)
{
	int	start;
	int	end;

	start = *i;
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
