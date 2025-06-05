#include "../includes/minishell.h"

int execute_cd(char **args, t_envp *env)
{
    char *tar_dir;
    char *old_pwd;
    char *new_pwd;

    new_pwd = NULL;
    tar_dir = NULL;
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
    {
        perror("cd: getcwd");
        return (1);
    }


    if (!args[0])
    {
        printf("error\n");
        tar_dir = ft_getenv("HOME", env);
    }
    else if(args[0]  &&     ft_strncmp(args[0], "-", 1) == 0)
        tar_dir = ft_getenv("OLDPWD", env);
    else
        tar_dir = args[0];

    if (!tar_dir || *tar_dir =='\0')
    {
        fprintf(stderr, "cd: target not set\n"); //use printf o
        // write(2,"cd: target not set\n",19);
        free(old_pwd);
        return (1);
    }
    if(chdir(tar_dir) != 0)
    {
        perror("cd");
        free(old_pwd);
        return (1);
    }
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
    {
        perror("cd: getcwd");
        return (1);
    }

    add_or_update_env(env, "OLDPWD", old_pwd);
    add_or_update_env(env, "PWD", new_pwd);


    free(old_pwd);
    free(new_pwd);
    return (0);
}
