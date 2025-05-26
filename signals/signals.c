#include "../mandatory/minishell.h"

void    sig_handler(int signal)
{
    // t_all   all;

    if (signal == SIGINT)
    {
        write(2, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    if (signal == SIGQUIT)
    {
        rl_replace_line("", 1);
        rl_redisplay();
    }
    // if (signal == SIGUSR1)
    //     ft_exit("FINISH\n", &all, 0);
}

void    signals_swing(void)
{
    struct sigaction    act;
    
    ft_bzero(&act, sizeof(act));
    act.sa_handler =  &sig_handler;
    sigaction(SIGINT, &act, NULL);   
    sigaction(SIGQUIT, &act, NULL);
}