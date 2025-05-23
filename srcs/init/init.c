#include "../includes/minishell.h"
void	init_token(t_tmptoken *tmp)
{
	tmp->start = 0;
	tmp->end = 0;
	tmp->value = NULL;
}

t_all *init_strcuts(t_all *as)
{     
    as = malloc(sizeof(t_all)); //free
    if(!as) exit_program(as, 1); 
    as->exit_status = 0;
    as->token = NULL;
    as->cmd =NULL;

    as->tmp = malloc(sizeof(t_tmptoken)); //free
    if (!as->tmp)
    {
        exit_program(as, 1); 
    }
  
    as->cp_envp = malloc(sizeof(t_envp)); //free
		if (!as->cp_envp)
            exit_program(as, 1); 
    return as;
}
char *cur_dir(t_all *as)
{
    char *path;
    char *cwd;
    path = NULL;
    cwd = NULL;
    cwd = getcwd(NULL,0);
    if(!cwd)
        exit_program(as, 1);
    path = ft_strjoin(cwd,"$ ");
    if(!path)
        exit_program(as, 1);
    free(cwd);
    return path;

}