#include "../includes/minishell.h"

int     if_nflag(char *str)
{
        int     i;

        i = 0;
        if(str[i] != '-')
                return (0);
                        
        if (!str[i])
                return (0);
        i = 1;
        if (!str[i])
                return (0);
        while(str[i])
        {
                if (str[i] != 'n')
                {
                        return (0);
                }
                i++;
             
        }
        return (1);
}

int    execute_echo(char **args)
{
        int     i;
        int     if_newline;

        if_newline = 1; //to check if we want a newline or not
        i = 1; // start from second command because first one is echo

        if (!args[1])
        {
                ft_putchar_fd('\n', 1);
                return 0;
        }        
        if(if_nflag(args[1]))
        {
                if_newline = 0;
                i++;
        }                
        while(args[i])
        {
                ft_putstr_fd((char *)args[i], 1);
                if (args[i + 1])
                        ft_putchar_fd(' ', 1);
                i++;
        }
        if(if_newline)
                ft_putchar_fd('\n', 1);
        return 0;
}