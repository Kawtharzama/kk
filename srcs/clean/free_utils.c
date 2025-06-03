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

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}

int	free_envp(t_envp *cp_envp)
{
	int	i;

	if (cp_envp && cp_envp->tmp_envp)
	{
		i = 0;
		while (i < cp_envp->counter)
		{
			free(cp_envp->tmp_envp[i]);
			i++;
		}
		free(cp_envp->tmp_envp);
		cp_envp->tmp_envp = NULL;
		free(cp_envp);
		cp_envp = NULL;
		return (1);
	}
	return (0);
}

void	free_all(t_all *as)
{
	if (as)
	{
		if (as->tmp)
		{
			free(as->tmp);
			as->tmp = NULL;
		}
		if (as->cp_envp)
		{
			free_envp(as->cp_envp);
			as->cp_envp = NULL;
		}
		if(as->child_pids)
		{
			free(as->child_pids);
			as->child_pids = NULL;
		}
		free(as);
		as = NULL;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		free(token);
		token = tmp;
	}
}

void	free_files(t_command *cmd)
{
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	if (cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
	}
}
