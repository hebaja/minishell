#ifndef MINISHELL_REDIRECT_H
# define MINISHELL_REDIRECT_H

# include "minishell_struct.h"

int	set_redirect_in(t_ms *ms, t_token *curr_token, int *tmp_fd_in);
int	set_redirect_out(int *tmp_fd_out, t_token *curr_token);
int	deal_redirect(t_cmd *cmd_curr);

#endif
