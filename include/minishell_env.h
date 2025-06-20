/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:47:09 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 16:47:11 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENV_H
# define MINISHELL_ENV_H

# include "minishell_struct.h"

int		env_lst_size(t_env *lst);
char	*build_env_sp(t_env *env);
char	**split_env(t_env *env_lst);
void	print_env(t_env *env_lst, t_cmd *cmd);
void	print_env_sort(t_env *env_lst, t_cmd *cmd);
void	ft_lstadd_back_env(t_env **env_head, t_env *new_node);
void	env_lst_remove_if(t_env **env_lst, char *value,
			int cmp(char *s1, char *s2));
void	env_lst_iterate(t_env *env_lst, void (*f)(t_env *env_lst));
void	env_lst_clear(t_env **env_lst);
t_env	*extract_key_and_value(char **envp, char *searchequal, t_env *env_lst);
t_env	*build_env_lst(int argc, char **argv, char **envp);

#endif
