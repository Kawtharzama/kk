#include "../includes/minishell.h"

int is_valid_key(char *key)
{
	int	i;

	i = 1;
	if (!key || !ft_isalpha(key[0]))
		return 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return 0;
		i++;
	}
	return 1;
}
void	end_update(t_envp *env, char *entry, char **new_env)
{
	int	i;

	i = -1;
	while(++i < env->counter)
		new_env[i] = env->tmp_envp[i];
	new_env[i++] = entry;
	new_env[i] = NULL;
	free(env->tmp_envp);
	env->tmp_envp = new_env;
	env->counter++;
}
void add_or_update_env(t_envp *env, char *key, char *value)
{
	int	i;
	char	*temp;
	char	*entry;
	char **new_env;

	i = 0;
	temp = ft_strjoin(key, "=");
	entry = ft_strjoin(temp, value);
	free(temp);
	while (i < env->counter)
	{
		if (ft_strncmp(env->tmp_envp[i], key, ft_strlen(key)) == 0 &&
				env->tmp_envp[i][ft_strlen(key)] == '=')
		{
			free(env->tmp_envp[i]);
			env->tmp_envp[i] = entry;
			return;
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (env->counter + 2));
	end_update(env, entry, new_env);
}
void    if_true(char **args, t_envp *env, char *equal_sign, int i)
{
	int key_len;
	char *key;
	char *value;

	key_len = equal_sign - args[i];
	key = ft_substr(args[i], 0, key_len);
	value = ft_strdup(equal_sign + 1);
	if (!is_valid_key(key))
		printf("export: `%s`: not a valid identifier\n", key);
	else
		add_or_update_env(env, key, value);
	free(key);
	free(value);
}
void	if_not(char **args, t_envp *env, int i)
{
	if (!is_valid_key(args[i]))
		printf("export: `%s`: not a valid identifier\n", args[i]);
	else
		add_or_update_env(env, args[i], ""); // Declare empty
}
// int execute_export(char **args, t_envp *env)
// {
// 	int i = 1;

// 	if (!args[1]) // Just `export`
// 	{
// 		int j = 0;
// 		while (j < env->counter)
// 		{
// 			if (ft_strchr(env->tmp_envp[j], '='))
// 				printf("declare -x %s\n", env->tmp_envp[j]);
// 			j++;
// 		}
// 		return 0;
// 	}
// 	while (args[i])
// 	{
// 		char *equal_sign = ft_strchr(args[i], '=');
// 		if (equal_sign)
// 			if_true(args, env, equal_sign, i);
// 		else
// 			if_not(args, env, i);
// 		i++;
// 	}
// 	return 0;
// }
void ft_sort_str_array(char **array)
{
	int	i;
	int	j;
	char *temp;

	i = 0;
	temp = NULL;
	while (array[i] != NULL)
	{
		j = i + 1;
		while (array[j] != NULL)
		{
			if (ft_strncmp(array[i], array[j], 4096) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}
void	print_export(char **sorted_env, int counter)
{
	int	i;
	char	*key;
	char	*value;

	i = 0;
	while (i < counter)
	{
		if (ft_strchr(sorted_env[i], '='))
		{
			key = ft_substr(sorted_env[i], 0, ft_strchr(sorted_env[i], '=') - sorted_env[i]);
			value = ft_strchr(sorted_env[i], '=') + 1;
			printf("declare -x %s=\"%s\"\n", key, value);
			free(key);
		}
		else
			printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	i = 0;
	while(sorted_env[i])
	{
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}
void no_args(t_envp *env)
{
	char **sorted_envp;
	int	i;

	i = 0;
	sorted_envp = malloc(sizeof(char *) * (env->counter + 1));
	if (!sorted_envp)
	{
		perror("malloc");
		return;
	}
	while (i < env->counter)
	{
		sorted_envp[i] = ft_strdup(env->tmp_envp[i]);
		i++;
	}
	sorted_envp[i] = NULL;
	ft_sort_str_array(sorted_envp);
	print_export(sorted_envp, env->counter);
}
int execute_export(char **args, t_envp *env)
{
	int i = 1;

	if (args[1] == NULL) // Just `export`
		no_args(env);
	else
	{
		while (args[i])
		{
			char *equal_sign = ft_strchr(args[i], '=');
			if (equal_sign)
			if_true(args, env, equal_sign, i);
			else
			if_not(args, env, i);
			i++;
		}
	}
	return 0;
}