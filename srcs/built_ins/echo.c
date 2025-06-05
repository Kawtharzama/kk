#include "../includes/minishell.h"

int     if_n(char *str)
{
        int     i;

        i = 0;
        while (str[i])
        {
                if (str[i] == 'n')
                        return (1);
                i++;
        }
        return (0);
}
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
        if(if_n(str))
                flag = 1; 
        while(str[i])
        {
                if (str[i] != 'n')
                {
                        if((str[i] == 'e' || str[i] == 'E') && flag)
                                ret = 1; //newline
                        else
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
        while(args[i][0] == '-')
        {
                if(if_nflag(args[i]))
                        if_newline = 0;
                i++;
        }                
        while(args[i])
        {
                ft_putstr_fd((char *)args[i], 1);
                if (args[i++ + 1])
                        ft_putchar_fd(' ', 1);
        }
        if(if_newline)
                ft_putchar_fd('\n', 1);
        return 0;
}
