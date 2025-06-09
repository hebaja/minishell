#include "../include/minishell.h"

void    handling_contrl(int sig)
{
    if (sig == SIGINT)
    {
        ft_printf("^C\n");
        sleep(500);
        exit_status(130);
        return ;
    }
    else if (sig == SIGQUIT)
    {
        ft_printf("exit\n");
        exit_status(0);
        exit(2);
    }
}

int    ft_signal(void)
{
    if (signal(SIGINT, handling_contrl) == 0 ||
        signal(SIGQUIT, handling_contrl))
        return (1);
    return (0);
}
