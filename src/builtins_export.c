/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:49:07 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/06 17:16:25 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	create_new_node(t_env *env, char *searchequal, t_token *variable)
{
	t_env	*new_node;
	int		size_key;
	int		size_value;

	size_key = searchequal - env;
	
}

t_token	*add_to_env_list(t_env *env, char *searchequal, t_token *variable)
{


	ft_lstadd_back(env, variable);

}

t_token	*create_variable(t_token *current, t_env *env)
{

	char	*searchequal;

	if (current->type != WORD)
		return (NULL);
	else
	{
		searchequal = ft_strchr(current->value, '=');

		printf("3: current->value = %s\n", current->value);
		printf("4: searchequal = %p\n", (void *)searchequal);

		if (searchequal)
			head->env = extract_key_and_value(env, searchequal, current);
		printf("5: depois de extract_key_and_value\n");
	}	
	return (head);

}
void	builtin_export(t_token *head, t_env *env)
{
	t_token *current;
	t_token	*export_head;
	t_env	*tmp;

	current = head->next;
	tmp = env;
	
	if (!current || current->type != WORD)
	{
		while (tmp)
		{
			ft_printf("%s=%s\n",tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	else
		export_head = create_variable(current, env);
}
