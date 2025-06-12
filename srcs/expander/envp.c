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

char	*search_path_dirs(char *path, char *cmd)
{
	char	*start;
	char	*end;
	char	*fullpath;

	start = path;
	end = ft_strchr(start, ':');
	while (end || *start)
	{
		if (end)
			*end = '\0';
		fullpath = get_full_path(start, cmd);
		if (end)
			*end = ':';
		if (fullpath)
			return (fullpath);
		if (end)
			start = end + 1;
		else
			break ;
		end = ft_strchr(start, ':');
	}
	return (NULL);
}

char	*find_path(t_envp *cp_envp, char *cmd)
{
	char	*path;

	path = ft_getenv("PATH", cp_envp);
	if (!path)
		return (NULL);
	return (search_path_dirs(path, cmd));
}

char	*ft_getenv(const char *name, t_envp *cp_envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	if (!name || !cp_envp || !cp_envp->tmp_envp)
		return (NULL);
	while (cp_envp->tmp_envp[i])
	{
		if (cp_envp->tmp_envp[i] && ft_strncmp(cp_envp->tmp_envp[i], name,
				len) == 0 && (cp_envp->tmp_envp[i][len]) == '=')
		{
			return (cp_envp->tmp_envp[i] + len + 1);
		}
		i++;
	}
	return ("");
}
