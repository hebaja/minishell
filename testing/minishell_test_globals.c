#include "../include/minishell.h"

int			i = 0;
int			res = 0;
int			cmd_res = 0;
char		**values = NULL;
char		**types = NULL;
char		**paths = NULL;
size_t		size = 0;
t_token		*token_lst = NULL;
t_env		*env_lst;
t_cmd		*cmd_lst = NULL;
