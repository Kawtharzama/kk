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

void	copy_envp(char **envp, t_all *as)
{
	int	count;
	int	r;

	r = 0;
	count = 0;
	while (envp[count])
		count++;
	as->cp_envp->tmp_envp = malloc(sizeof(char *) * (count + 1));
	if (!as->cp_envp->tmp_envp)
		exit_program(as, "Malloc Fail", 1);
	while (envp[r])
	{
		as->cp_envp->tmp_envp[r] = ft_strdup(envp[r]);
		if (!as->cp_envp->tmp_envp[r])
			exit_program(as, "Malloc Fail", 1);
		r++;
	}
	as->cp_envp->tmp_envp[r] = NULL;
	as->cp_envp->counter = r;
}

char	*get_full_path(char *dir, char *cmd)
{
	char	*addslash;
	char	*fullpath;

	addslash = ft_strjoin(dir, "/");
	fullpath = ft_strjoin(addslash, cmd);
	free(addslash);
	if (access(fullpath, X_OK) == 0)
	{
		return (fullpath);
	}
	free(fullpath);
	
	return (NULL);
}

char	*find_path(t_envp *cp_envp, char *cmd)
{
	char	*path;
	char	*start;
	char	*end;
	char	*fullpath;

	path = ft_getenv("PATH", cp_envp);

	if (!path)
		return (NULL);
	start = path;
	end = ft_strchr(start, ':');
	while (end || *start)
	{
		if (end)
			*end = '\0';
		fullpath = get_full_path(start, cmd);
		
		if (fullpath)
			return (fullpath);
		// free(fullpath);
		if (end)
			start = end + 1;
		else
			break ;
		end = ft_strchr(start, ':');
	}
	return (NULL);
}

void	print_envp(t_envp *cp_envp)
{
	int		r;

	r = 0;
	while (cp_envp->tmp_envp[r])
	{
		printf("%s\n", cp_envp->tmp_envp[r]);
		r++;
	}
}
