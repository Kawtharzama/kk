#include "../includes/minishell.h"

int execute_pwd(char **args)
{
    char *cwd;

    (void)args; // we ignore args, since pwd doesn’t take any

    cwd = getcwd(NULL, 0); // get current directory (allocates memory just enough for full path string)
    if (!cwd)
    {
        perror("pwd");
        return 1;
    }

    printf("%s\n", cwd); // print to stdout
    free(cwd); // avoid memory leaks
    return 0;
}
