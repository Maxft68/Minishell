#include "../mandatory/minishell.h"

void    sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        write(1, "^C", 2);
    }
}

void    signals_swing(void)
{
    struct sigaction    act;
    
    ft_bzero(&act, sizeof(act));
    act.sa_handler =  &sig_handler;
    sigaction(SIGINT, &act, NULL);   
}