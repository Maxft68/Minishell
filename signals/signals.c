#include "../mandatory/minishell.h"

void    sig_handler(int signal)
{
    // t_all   all;

    if (signal == SIGINT)
    {
        write(2, "\nWriteToMe\r", 11);
        // create_lexer(readline("\nWriteOnMe "), &all);
        // break;
        // ft_exit("\nFINISH\n", &all, 0);
    }
}

void    signals_swing(void)
{
    struct sigaction    act;
    
    ft_bzero(&act, sizeof(act));
    act.sa_handler =  &sig_handler;
    sigaction(SIGINT, &act, NULL);   
}