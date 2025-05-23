#include "../includes/minishell.h"

void exit_program(t_all *as, int n)
{
    clean(as);
    as->exit_status = n ;
    exit(n);
}