#include "../includes/minishell.h"

void print_commands(t_command *cmd_list)
{
	return ;
	int i;
	int cmd_num = 1;
	t_command *cmd = cmd_list;

	while (cmd)
	{
		printf("=== Command %d ===\n", cmd_num);

		// Print arguments
		if (cmd->args)
		{
			printf("Arguments:\n");
			for (i = 0; cmd->args[i]; i++)
				printf("  [%d]: %s\n", i, cmd->args[i]);
		}
		else
		{
			printf("Arguments: None\n");
		}

		// Print infile
		if (cmd->infile)
			printf("Infile: %s\n", cmd->infile);
		else
			printf("Infile: None\n");

		// Print outfile
		if (cmd->outfile)
			printf("Outfile: %s (append: %s)\n", cmd->outfile, cmd->append ? "yes" : "no");
		else
			printf("Outfile: None\n");
		if (cmd->heredoc)
			printf("Herdoc : %d", cmd->heredoc);

		printf("\n");
		cmd = cmd->next;
		cmd_num++;
	}
}

t_command *new_command(t_all *as)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		exit_program(as, "Memory allocation failed", 1);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	cmd->heredoc = 0;
	cmd->executable = 1;
	return cmd;
}

char **add_arg(t_all *as, char **args, char *value)
// appends a new argument string to the end of the args array (resizing as needed)
{
	int count; // to count amount of args
	int i;

	i = 0;
	count = 0;
	while (args && args[count])
		count++;

	char **new_args = malloc(sizeof(char *) * (count + 2)); // allocates one more for the new arg and NULL
	if (!new_args)
		exit_program(as, "Memory allocation failed", 1);
	while (i < count)
	// copy existing args to new array
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[count] = ft_strdup(value); // adds the new arg to the end
	new_args[count + 1] = NULL;

	if (args)
		free(args); // reallocated, old pointer is no longer used
	// frees the old args array but not the strings inside it
	return new_args;
}

void append_command(t_command **cmd_list, t_command *new_cmd)
{
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		return;
	}

	t_command *tmp = *cmd_list;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = new_cmd; // link the new command to the end of the list
}

int split_cmds(t_all *as, t_token *token, t_command **cmd_list)
// splits the token list into a command list
{
	*cmd_list = NULL; // starts with an empty command list
	t_command *current_cmd = new_command(as);
	if (!current_cmd)
	{
		free(current_cmd); // ask
		exit_program(as, "Memory allocation failed", 1);
	}

	while (token)
	// iterate through the token list
	{
		if (token->type == WORD)
		{
			current_cmd->args = add_arg(as, current_cmd->args, token->value);
			if (!current_cmd->args)
				exit_program(as, "Memory allocation failed", 1);
		}
		else if (token->type == HEREDOC)
		{
			if (!token->next || token->next->type != WORD)
			{
				exit_program(as, "Memory allocation failed", 1); // no
			}
			current_cmd->heredoc = 1;
			int n = ft_strlen(token->next->value);
			current_cmd->infile = heredoc_cmd(as, token->next->value, n);
			token = token->next;
		}
		else if (token->type == REDIR)
		{
			if (!token->next || token->next->type != WORD)
			{

				return -2;
			}

			if (ft_strncmp(token->value, ">", 1) == 0)
			{
				if (ft_strncmp(token->value, ">>", 2) == 0)
					current_cmd->append = 1;
				if (current_cmd->outfile)
					free(current_cmd->outfile);
				current_cmd->outfile = ft_strdup(token->next->value); // ask how to free??
				int fd_out = open(current_cmd->outfile, current_cmd->append ? O_WRONLY | O_CREAT | O_APPEND : O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd_out == -1)
				{
					perror("outfile");
					as->exit_status = 1;
					current_cmd->executable = 0;
				}
				else
					close(fd_out);
			}
			else if (ft_strncmp(token->value, "<", 1) == 0)
			{
				if (current_cmd->infile)
					free(current_cmd->infile);
				current_cmd->infile = ft_strdup(token->next->value);

				int fd_in = open(current_cmd->infile, O_RDONLY);
				if (fd_in == -1)
				{
					perror("infile");
					as->exit_status = 1;
					current_cmd->executable = 0;
				}
				else
					close(fd_in);
			}

			token = token->next;
		}
		else if (token->type == PIPE)
		{
			append_command(cmd_list, current_cmd);
			current_cmd = new_command(as);
			if (!current_cmd)
				exit_program(as, "Memory allocation failed", 1);
		}

		token = token->next;
	}

	// if (current_cmd->args)
		append_command(cmd_list, current_cmd);

	return 0;
}
