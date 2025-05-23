#include "../includes/minishell.h"

void free_args(char **args)
{
    int i;
    i = 0;
    if(!args)
        return;
    while(args[i])
    {
        free(args[i]);
        args[i] = NULL;
        i++;
    }
    free(args);
    args = NULL;
}
int free_envp(t_envp *cp_envp)
{
    int i;

    if (cp_envp && cp_envp->tmp_envp)
    {
        i = 0;
        while (i < cp_envp->counter)
        {
            free(cp_envp->tmp_envp[i]);
            i++;
        }
        free(cp_envp->tmp_envp);
        cp_envp->tmp_envp = NULL;

        free(cp_envp);
        cp_envp = NULL;
        return 1; // exit
    }
    return 0; // exit
}

void free_all(t_all *as)
{
    if (as)
    {
        // clean(as->token);
        if (as->tmp)
        {
            free(as->tmp); // end of project
            as->tmp = NULL;
        }

        if (as->cp_envp)
        {
            free_envp(as->cp_envp); // end of project
            as->cp_envp = NULL;
        }

        free(as); // end of project
        as = NULL;
    }
}

void free_tokens(t_token *token)
{
    t_token *tmp;

    while (token)
    {
        tmp = token->next;

        if (token->value)
        {
            free(token->value);
            token->value = NULL;
        }
        free(token);

        token = tmp;
    }
}

void free_cmd(t_command *cmd)
{
    t_command *tmp;

    while (cmd)
    {
        tmp = cmd->next;

        if (cmd->args)
        {
            int i = 0;
            while (cmd->args[i])
            {
                free(cmd->args[i]);
                cmd->args[i] = NULL;
                i++;
            }
            free(cmd->args);
            cmd->args = NULL;
        }

        if (cmd->infile)
        {
            free(cmd->infile);
            cmd->infile = NULL;
        }

        if (cmd->outfile)
        {
            free(cmd->outfile);
            cmd->outfile = NULL;
        }

        free(cmd);
        cmd = tmp;
    }
}

int free_token_cmd(t_all *as)
{
    if (as)
    {
        free_tokens(as->token);
        as->token = NULL;

        free_cmd(as->cmd);
        as->cmd = NULL;
    }
    return 0; // exit
}

int clean(t_all *as)
{
    if (as)
    {
        free_token_cmd(as);
        free_all(as);
    }
    return 0; // exit
}
