/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:14:51 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/06/12 17:14:57 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	join_after_and_replace(t_token *token, char *var_value, int end, int len)
{
	char	*after;
	char	*tmp;

	after = NULL;
	if (end + 1 < len)
	{
		after = ft_substr(token->value, end, len);
		if (!after)
			return (free(var_value), -1); 
		tmp = var_value;
		var_value = ft_strjoin(var_value, after);
		if (!var_value)
			return (free(after), free(tmp), -1); 
		free(after);
		free(tmp);
	}
	free(token->value);
	token->value = var_value;
	return (0);
}

int	expand_variable(t_token *token, char *env_value, int start, int end)
{
	char	*var_value;
	int		len;

	len = ft_strlen(token->value);
	var_value = join_before_env(token, env_value, start);
	if (!var_value)
		return (-1); 
	return (join_after_and_replace(token, var_value, end, len));
}

int	process_dollar(t_all *as, t_token *token, int *i, t_envp *cp_envp)
{
	char	*var;
	int		start;
	char	*env_value;
	int		end;

	(*i)++;
	if (token->value[*i] == '?')
		return (handle_exit_status(as, token));
	start = extract_variable(as, token->value, i, &var);
	if (start == -1)
		return (-1);
	env_value = ft_getenv(var, cp_envp);
	free(var);
	end = *i;
	if (expand_variable(token, env_value, start, end) == -1)
		return (-1);
	return (1);
}

int	process_token(t_all *as, t_token *token, t_envp *cp_envp)
{
	int	i;
	int	in_double;

	i = 0;
	in_double = 0;
	while (token->value[i])
	{
		if (handle_single_quotes(token->value, &i, in_double))
			continue ;
		in_double = toggle_double_quote(token->value[i], in_double);
		if (token->value[i] == '$')
		{
			if (process_dollar(as, token, &i, cp_envp) == -1)
				return (-1);
			i = 0;
			in_double = 0;
			continue ;
		}
		i++;
	}
	return (0);
}

int	expand_var(t_all *as, t_token *token, t_envp *cp_envp)
{
	while (token)
	{
		if (token->prev && token->prev->type == HEREDOC)
			return (0);
		if (token->type == WORD)
		{
			if (process_token(as, token, cp_envp) == -1)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}
