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

static int handle_single_quotes(const char *value, int *i, int in_double)
{
    if (value[*i] == '\'' && in_double == 0)
    {
        (*i)++;
        while (value[*i] && value[*i] != '\'')
            (*i)++;
        (*i)++;
        return 1;
    }
    return 0;
}

static int toggle_double_quote(int ch, int in_double)
{
    if (ch == '"')
        return !in_double;
    return in_double;
}

static int handle_exit_status(t_all *as, t_token *token)
{
    // printf("%d", as->exit_status);
    char *status_str;

    if (!token || !token->value)
        return 0;

    free(token->value);
    status_str = ft_itoa(as->exit_status);
    if (!status_str)
        exit_program(as, "Memory allocation failed", 1);

    token->value = status_str;
    return 1;
}

static int extract_variable(t_all *as,  char *value, int *i, char **var)
{
    int start = *i;
    while (value[*i] && (isalnum(value[*i]) || value[*i] == '_'))
        (*i)++;
    int end = *i;
    *var = ft_substr(value, start, end - start);
    if (!*var)
    {
        exit_program(as, "Memory allocation failed", 1);
    }
    return start;
}

static char *join_before_env(t_token *token, char *env_value, int start)
{
    char *before = NULL;
    char *var_value = ft_strdup(env_value);
    char *tmp;

    if (!var_value)
        return NULL;

    if (start > 1)
    {
        before = ft_substr(token->value, 0, start - 1);
        if (!before)
        {
            return (free(var_value),NULL); //ask shall we add exit

        }
        tmp = var_value;
        var_value = ft_strjoin(before, var_value);
        if(!var_value)
            return (free(before), free(tmp), NULL);//ask shall we add exit

        free(before);
        free(tmp);
    }
    return var_value;
}


static int join_after_and_replace(t_token *token, char *var_value, int end, int len)
{
    char *after = NULL;
    char *tmp;

    if (end + 1 < len)
    {
        after = ft_substr(token->value, end, len);
        if (!after)
     
            return (free(var_value),-1);//ask shall we add exit
         
        tmp = var_value;
        var_value = ft_strjoin(var_value, after);
        if (!var_value)
            return (free(after), free(tmp), -1);//ask shall we add exit

        free(after);
        free(tmp);
    }
    free(token->value);
    token->value = var_value;
    return 0;
}


static int expand_variable(t_token *token, char *env_value, int start, int end, int len)
{
    char *var_value = join_before_env(token, env_value, start);
    if (!var_value)
        return -1; //ask shall we add exit

    return join_after_and_replace(token, var_value, end, len);
}


static int process_dollar(t_all *as, t_token *token, int *i, t_envp *cp_envp)
{
    (*i)++;
    if (token->value[*i] == '?')
        return handle_exit_status(as, token);

    char *var;
    int start = extract_variable(as, token->value, i, &var);
    if (start == -1)
        return -1;

    char *env_value = ft_getenv(var, cp_envp);
    free(var);

    int len = ft_strlen(token->value);
    int end = *i;

    if (expand_variable(token, env_value, start, end, len) == -1)
        return -1;
    return 1;
}

static int process_token(t_all *as, t_token *token, t_envp *cp_envp)
{
    int i = 0;
    int in_double = 0;
    // int ret;
    

    while (token->value[i])
    {
        if (handle_single_quotes(token->value, &i, in_double))
            continue;
        in_double = toggle_double_quote(token->value[i], in_double);
        if (token->value[i] == '$')
        {
             process_dollar(as, token, &i, cp_envp);
            // if(ret == -1)
            //     return -1;  
            i = 0;
            in_double = 0;
            continue;                  
    
        }
         i++;
    }
    return 0;
}

int expand_var(t_all *as, t_token *token , t_envp *cp_envp)
{
    while (token)
    {
        if (token->prev && token->prev->type == HEREDOC)
            return 0;
        if (token->type == WORD)
        {
            if (process_token(as, token, cp_envp) == -1)
                return -1;
        }
        token = token->next;
    }
    return 0;
}


// int expand_var(t_all *as, t_token *token , t_envp *cp_envp)
// {
//     char *var_value ;

//     while (token)
//     {
//         if(token->prev && token->prev->type == HEREDOC)
//             return 0;
//         if (token->type == WORD)
//         {
            
//             int i = 0;
//             int in_double = 0;
//             int len = ft_strlen(token->value);


//             while (token->value[i])
//             {
//                 if (token->value[i] == '\'' && in_double == 0)
//                 {
//                     i++;
//                     while (token->value[i] && token->value[i] != '\'')
//                         i++;
//                    i++;
//                    continue;
//                 }
//                 else if (token->value[i] == '"')
//                 {
//                     if (in_double == 0)
//                         in_double = 1;
//                     else
//                         in_double = 0;
//                 }
//                 else if (token->value[i] == '$')
//                 {
                    
//                     i++;
//                     if(token->value[i] == '?')
//                     {
//                         printf("%d",as->exit_status);
//                         free(token->value);
//                         token->value = ft_itoa(as->exit_status);//TODO: free?
//                         break;
//                     }
//                    int start = i;
//                    while( token->value[i] &&( isalnum(token->value[i]) || token->value[i] == '_'))
//                    {
//                     i++;
//                  }
//                     int end = i;
//                     char *var = ft_substr(token->value, start,(end - start));
//                     if(!var)
//                     {
//                         perror("Memory allocation failed for token.value\n");
//                         return -1;

//                     }
//                     char *env_value = ft_getenv(var, cp_envp);
//                         free(var);
                    
//                     var_value = ft_strdup(env_value); 
            
//                 if(start > 1)
//                 {
//                     char *before = ft_substr(token->value, 0, start - 1);
//                     if(!before)
//                     {
//                         perror("Memory allocation failed for token.value\n");
//                         return -1;

//                     }

//                     char *tmp=var_value;
//                     // if (before)
//                         // printf("Value of bef: %s\n", before);
//                     var_value = ft_strjoin(before, var_value);
//                     free(tmp);
//                     free(before);



//                 }
//                 if(end + 1 < len)
//                 {
//                     char *after = ft_substr(token->value, end, len);
//                     if(!after)
//                     {
//                         perror("Memory allocation failed for token.value\n");
//                         return -1;

//                     }
//                     // if (after)
                        
//                     char *tmp=var_value;// printf("Value of af: %s\n", after);
//                         var_value = ft_strjoin(var_value, after);
//                         free(tmp);
//                         free(after);
                        
//                 }
//                 free(token->value);
//                 token->value =  var_value;

//                 printf("Value: %s\n", var_value);
                

//                 }
//                 i++;
//             }
//         }
        
//         token = token->next;
     
//     }
//     return 0;
// }



//read is alnum and _
//save the before if there is (i value)
//extract use substr
//use getenvp to extract it
//join before var after
//check for $
//substr the var 
//get envp in the envp
//new token join all together,