/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirect.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:36:23 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/25 11:36:25 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_REDIRECT_H
# define MINISHELL_REDIRECT_H

# include "minishell_struct.h"

int	set_redirect_in(t_ms *ms, t_token *curr_token, int *tmp_fd_in);
int	set_redirect_out(int *tmp_fd_out, t_token *curr_token);
int	deal_redirect(t_cmd *cmd_curr);

#endif
