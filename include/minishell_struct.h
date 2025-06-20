/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:47:35 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 16:47:37 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include "minishell_enum.h"

typedef struct s_env
{
	int				printed;
	char			*value;
	char			*key;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	int				join;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	int				fds[2];
	int				fd_out;
	int				fd_in;
	int				pid;
	int				is_piped;
	int				is_end;
	int				is_single;
	char			*path;
	char			**args;
	t_token_type	main_type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_ms
{
	t_token			*token_lst;
	t_env			*env_lst;
	t_cmd			*cmd_lst;
	char			**paths;
	char			*input;
	int				status;
	int				is_exit;
}	t_ms;

#endif
