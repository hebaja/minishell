#include "../include/minishell.h"

int    handling_contrl(int sig)
{
    if (sig == SIGINT)
    {
        ft_printf("^C\n");
        sleep(500);
        exit_status(130);
        return (1);
    }
    else if (sig == SIGQUIT)
    {
        ft_printf("exit\n");
        exit_status(0);
        exit(2);
    }
    return (0);
}

int    ft_signal(void)
{
    if (signal(SIGINT, handling_contrl) ||
        signal(SIGQUIT, handling_contrl))
        return (1)
    return (0);
}
