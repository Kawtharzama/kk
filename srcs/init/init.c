/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	init_token(t_tmptoken *tmp)
{
	tmp->start = 0;
	tmp->end = 0;
	tmp->value = NULL;
}

t_all	*init_strcuts(t_all *as)
{
	as = malloc(sizeof(t_all));
	if (!as)
		exit_program(as, "Memory allocation failed", 1);
	as->exit_status = 0;
	as->token = NULL;
	as->cmd = NULL;
	as->tmp = malloc(sizeof(t_tmptoken));
	if (!as->tmp)
	{
		exit_program(as, "Memory allocation failed", 1);
	}
	as->cp_envp = malloc(sizeof(t_envp));
	if (!as->cp_envp)
		exit_program(as, "Memory allocation failed", 1);
	as->child_pids = NULL;

	return (as);
}

char	*cur_dir(t_all *as)
{
	char	*path;
	char	*cwd;

	path = NULL;
	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit_program(as, "Memory allocation failed", 1);
	path = ft_strjoin(cwd, "$ ");
	if (!path)
		exit_program(as, "Memory allocation failed", 1);
	free(cwd);
	return (path);
}
