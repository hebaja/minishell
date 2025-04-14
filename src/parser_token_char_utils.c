#include "../include/minishell.h"

int	is_metacharacter(char *value)
{
	if ((ft_strncmp(value, ">>", 2) == 0) || (ft_strncmp(value, "<<", 2) == 0)
		|| (ft_strncmp(value, "&&", 2) == 0) || (ft_strncmp(value, "||", 2) == 0))
 		return (2);
	if ((ft_strncmp(value, "|", 1) == 0) || (ft_strncmp(value, ">", 1) == 0)
		|| (ft_strncmp(value, "<", 1) == 0) || (ft_strncmp(value, "&", 1) == 0))
		return (1);
	return (0);
}
