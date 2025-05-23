#include "../includes/minishell.h"

void sig_handler_prompt (int signum)
{
    if(signum == SIGINT )
    {
        write(1, "\n", 1);                
        rl_replace_line("", 0);          
        rl_on_new_line();               
        rl_redisplay(); 
    }
}
void setup_signals(void)
{
    signal(SIGINT, sig_handler_prompt);
    signal(SIGQUIT, SIG_IGN);
}
void restore_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}