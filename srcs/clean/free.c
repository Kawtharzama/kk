/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				cmd->args[i] = NULL;
				i++;
			}
			free(cmd->args);
			cmd->args = NULL;
		}
		free_files(cmd);
		free(cmd);
		cmd = tmp;
	}
}

int	free_token_cmd(t_all *as)
{
	if (as)
	{
		free_tokens(as->token);
		as->token = NULL;
		free_cmd(as->cmd);
		as->cmd = NULL;
	}
	return (0);
}

int	clean(t_all *as)
{
	if (as)
	{
		free_token_cmd(as);
		free_all(as);
	}
	return (0);
}
