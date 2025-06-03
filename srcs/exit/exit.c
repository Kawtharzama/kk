/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_program(t_all *as, char *str, int n)
{
	if (as)
		as->exit_status = n;
	clean(as);
		perror(str);
	exit(n);
}

void	exit_fork(t_all *as, char *str)
{
	clean(as);
		perror(str);
	exit(EXIT_FAILURE);
}

void	exit_forkk(t_all *as, char *str, int n)
{
	as->exit_status = n;
	clean(as);
	if (str)
		perror(str);
	exit(n);
}
