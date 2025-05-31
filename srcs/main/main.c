/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:54:43 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/31 17:54:53 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

void	setup_environment(int argc, char **argv, char **envp, t_all **as)
{
	(void)argc;
	(void)argv;
	*as = init_strcuts(NULL);
	if (!*as)
		exit_program(*as, "error in init all structs strcut", 1);
	copy_envp(envp, *as);
}

void	start_shell(t_all *as)
{
	char	*input;
	char	*path;

	while (1)
	{
		path = cur_dir(as);
		setup_signals();
		input = readline(path);
		free(path);
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		ignore_signals();
		add_history(input);
		toknize(input, as);
		free(input);
		free_token_cmd(as);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_all	*as;

	as = NULL;
	setup_environment(argc, argv, envp, &as);
	start_shell(as);
	clean(as);
	return (0);
}
