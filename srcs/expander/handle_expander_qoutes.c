/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expander_qoutes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:12 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/06/12 19:03:51 by kabu-zee         ###   ########.fr       */
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
