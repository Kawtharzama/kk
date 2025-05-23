#include "../includes/minishell.h"

char *ft_getenv(const char *name,t_envp *cp_envp)
{
    int i =0;
    int len = ft_strlen(name);
    if (!name || !cp_envp || !cp_envp->tmp_envp)
        return NULL;
    while(cp_envp->tmp_envp[i])
    {
        if(cp_envp->tmp_envp[i] && ft_strncmp(cp_envp->tmp_envp[i], name, len) == 0 && (cp_envp->tmp_envp[i][len]) == '=')
        {
            return cp_envp->tmp_envp[i] + len + 1;
        }
        i++;
    }
    return "";
}

int expand_var(t_all *as, t_token *token , t_envp *cp_envp)
{
    char *var_value ;

    while (token)
    {
        if (token->type == WORD)
        {
            int i = 0;
            int in_double = 0;
            int len = ft_strlen(token->value);


            while (token->value[i])
            {
                if (token->value[i] == '\'' && in_double == 0)
                {
                    i++;
                    while (token->value[i] && token->value[i] != '\'')
                        i++;
                   i++;
                   continue;
                }
                else if (token->value[i] == '"')
                {
                    if (in_double == 0)
                        in_double = 1;
                    else
                        in_double = 0;
                }
                else if (token->value[i] == '$')
                {
                    
                    i++;
                    if(token->value[i] == '?')
                    {
                        printf("%d",as->exit_status);
                        free(token->value);
                        token->value = ft_itoa(as->exit_status);//free?
                        break;
                    }
                   int start = i;
                   while( token->value[i] &&( isalnum(token->value[i]) || token->value[i] == '_'))
                   {
                    i++;
                 }
                    int end = i;
                    char *var = ft_substr(token->value, start,(end - start));
                    char *env_value = ft_getenv(var, cp_envp);
                        free(var);
                    
                    var_value = ft_strdup(env_value); 
            
                if(start > 1)
                {
                    char *before = ft_substr(token->value, 0, start - 1);

                    char *tmp=var_value;
                    // if (before)
                        // printf("Value of bef: %s\n", before);
                    var_value = ft_strjoin(before, var_value);
                    free(tmp);
                    free(before);



                }
                if(end + 1 < len)
                {
                    char *after = ft_substr(token->value, end, len);
                    // if (after)
                        
                    char *tmp=var_value;// printf("Value of af: %s\n", after);
                        var_value = ft_strjoin(var_value, after);
                        free(tmp);
                        free(after);
                        
                }
                free(token->value);
                token->value =  var_value;

                printf("Value: %s\n", var_value);
                

                }
                i++;
            }
        }
        
        token = token->next;
     
    }
    return 0;
}



//read is alnum and _
//save the before if there is (i value)
//extract use substr
//use getenvp to extract it
//join before var after
//check for $
//substr the var 
//get envp in the envp
//new token join all together,