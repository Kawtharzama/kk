#include "../includes/minishell.h"

int is_valid_key(char *key)
{
    if (!key || !ft_isalpha(key[0]))
        return 0;
    for (int i = 1; key[i]; i++)
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return 0;
    }
    return 1;
}

void add_or_update_env(t_envp *env, char *key, char *value)
{
    int i = 0;
    char *entry = ft_strjoin(ft_strjoin(key, "="), value);

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

    // Append new entry
    char **new_env = malloc(sizeof(char *) * (env->counter + 2));
    for (i = 0; i < env->counter; i++)
        new_env[i] = env->tmp_envp[i];
    new_env[i++] = entry;
    new_env[i] = NULL;
    free(env->tmp_envp);
    env->tmp_envp = new_env;
    env->counter++;
}

int execute_export(char **args, t_envp *env)
{
    int i = 1;

    if (!args[1]) // Just `export`
    {
        for (int j = 0; j < env->counter; j++)
        {
            if (ft_strchr(env->tmp_envp[j], '='))
                printf("declare -x %s\n", env->tmp_envp[j]);
        }
        return 0;
    }

    while (args[i])
    {
        char *equal_sign = ft_strchr(args[i], '=');

        if (equal_sign)
        {
            int key_len = equal_sign - args[i];
            char *key = ft_substr(args[i], 0, key_len);
            char *value = ft_strdup(equal_sign + 1);

            if (!is_valid_key(key))
                printf("export: `%s`: not a valid identifier\n", key);
            else
                add_or_update_env(env, key, value);

            free(key);
            free(value);
        }
        else
        {
            if (!is_valid_key(args[i]))
                printf("export: `%s`: not a valid identifier\n", args[i]);
            else
                add_or_update_env(env, args[i], ""); // Declare empty
        }

        i++;
    }

    return 0;
}
