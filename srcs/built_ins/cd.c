#include "../includes/minishell.h"

#include "../includes/minishell.h"

void update_env_var(t_envp *env, const char *key, const char *value)
{
    int i = 0;
    char *tmp = ft_strjoin(key, "=");
    if (!tmp)
        return;

    char *new_entry = ft_strjoin(tmp, value);
    free(tmp);
    if (!new_entry)
        return;

    // Try to update existing variable
    while (i < env->counter)
    {
        if (ft_strncmp(env->tmp_envp[i], key, ft_strlen(key)) == 0 &&
            env->tmp_envp[i][ft_strlen(key)] == '=')
        {
            free(env->tmp_envp[i]);
            env->tmp_envp[i] = new_entry;
            return;
        }
        i++;
    }

    // Not found, so append it
    char **new_env = malloc(sizeof(char *) * (env->counter + 2));
    if (!new_env)
    {
        free(new_entry);
        return;
    }

    for (int j = 0; j < env->counter; j++)
        new_env[j] = env->tmp_envp[j];

    new_env[env->counter] = new_entry;
    new_env[env->counter + 1] = NULL;

    free(env->tmp_envp);
    env->tmp_envp = new_env;
    env->counter++;
}


int execute_cd(char **args, t_envp *env)
{
    char *target_dir;
    char *old_pwd = getcwd(NULL, 0);
    printf("Before cd: %s\n", old_pwd);

    if (!old_pwd)
    {
        perror("getcwd");
        return 1;
    }

    if (!args[1])
    {
        target_dir = ft_getenv("HOME", env);
        if (!target_dir || *target_dir == '\0')
        {
            fprintf(stderr, "cd: HOME not set\n");
            free(old_pwd);
            return 1;
        }
    }
    else
    {
        target_dir = args[1];
    }

    printf("Trying to cd into: %s\n", target_dir);

    if (chdir(target_dir) != 0)
    {
        perror("cd");
        free(old_pwd);
        return 1;
    }

    char *new_pwd = getcwd(NULL, 0);
    printf("After cd: %s\n", new_pwd);

    update_env_var(env, "OLDPWD", old_pwd);
    update_env_var(env, "PWD", new_pwd);

    free(old_pwd);
    free(new_pwd);
    return 0;
}
