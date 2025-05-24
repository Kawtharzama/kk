#include "../includes/minishell.h"

int execute_env(char **args, t_envp *env)
{
    int i = 0;

    if (args[1])
    {
        printf("env: too many arguments\n");
        return 1;
    }

    while (i < env->counter && env->tmp_envp[i])
    {
        if (ft_strchr(env->tmp_envp[i], '=')) // only print key=value
            printf("%s\n", env->tmp_envp[i]);
        i++;
    }
    return 0;
}
