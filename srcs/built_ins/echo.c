#include "../includes/minishell.h"

int     if_nflag(char *str)
{
        int     i;
        int     flag;
        int ret;

        ret = 0;
        flag = 0;
        i = 0;
        if(str[i] != '-' || !str[i]) 
                return (0); //newline
        i = 1; 
        while(str[i])
        {
                if (str[i] == 'n')
                {
                        flag = 1;
                        ret = 1;
                }
                if ((str[i] == 'e' || str[i] == 'E') && flag == 1)
                        ret = 1;
                if (str[i] != 'n')
                        return (0); //newline
                i++;
        }
        return (ret);
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