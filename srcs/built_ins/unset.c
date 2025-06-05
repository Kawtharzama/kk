#include "../includes/minishell.h"

int is_valid_unset_key(char *key)
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

void remove_env_var(t_envp *env, const char *key)
{
    int i = 0, j = 0;
    int len = ft_strlen(key);
    char **new_env = malloc(sizeof(char *) * (env->counter + 1)); // worst case: all remain except 1
    if (!new_env)
        return;

    while (i < env->counter)
    {
        if (ft_strncmp(env->tmp_envp[i], key, len) == 0 && env->tmp_envp[i][len] == '=')
        {
            free(env->tmp_envp[i]); // don't copy this one
        }
        else
        {
            new_env[j++] = ft_strdup(env->tmp_envp[i]);
        }
        i++;
    }
    new_env[j] = NULL;
    free(env->tmp_envp);
    env->tmp_envp = new_env;
    env->counter = j;
}

int execute_unset(char **args, t_envp *env)
{
    for (int i = 1; args[i]; i++)
    {
        if (!is_valid_unset_key(args[i]))
        {
            printf("unset: `%s`: not a valid identifier\n", args[i]);
            continue;
        }
        remove_env_var(env, args[i]);
    }
    return 0;
}
