#include "../includes/minishell.h"

void copy_envp(char **envp, t_all *as)
	{
		
		int count ;
		int r ;
		r = 0;
		
		count = 0 ;
		while(envp[count])
			count++;
		as->cp_envp->tmp_envp = malloc(sizeof(char*) * (count+1)); //free
		if (!as->cp_envp->tmp_envp)
        	exit_program(as, 1); //exit function
		while(envp[r])
		{
			as->cp_envp->tmp_envp[r] = ft_strdup(envp[r]);
        	if (!as->cp_envp->tmp_envp[r])
				exit_program(as, 1); //exit function

			
			r++;
		}
		as->cp_envp->tmp_envp[r] = NULL;
		as->cp_envp->counter = r;
		
	}

	char *get_full_path(char *dir, char *cmd) {
		char *addslash;
		char *fullpath;
	
		addslash = ft_strjoin(dir, "/");
		fullpath = ft_strjoin(addslash, cmd);
		free(addslash);
	
		if (access(fullpath, X_OK) == 0) {
			return fullpath;
		}
	
		free(fullpath);
		return NULL;
	}
char *find_path(t_envp *cp_envp, char *cmd) {
    char *path;
    char *start;
    char *end;
    char *fullpath;

    path = ft_getenv("PATH", cp_envp);
    if (!path) 
        return NULL;
    
    start = path;
    while ((end = ft_strchr(start, ':')) || *start) 
    {
        if (end) 
            *end = '\0';     
       	fullpath = get_full_path(start, cmd);
        if (fullpath) 
        {
            // printf("%s\n", fullpath);
            return fullpath;
        } //delete it before submit
        free(fullpath);
        if (end) 
            start = end + 1; 
        else
            break; //does check the last dir?
    }
    return NULL;
}

	void print_envp(t_envp *cp_envp)
	{
		int r = 0 ;
		while(cp_envp->tmp_envp[r])
		{
			printf("%s\n", cp_envp->tmp_envp[r]);
			r++;
		}

	}