/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:49:07 by alda-sil          #+#    #+#             */
/*   Updated: 2025/04/25 20:43:35 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstadd_back_export(t_token **export_head, t_token *new_node)
{
	t_token *tmp;

	if (!*export_head)
		*export_head = new_node;
	else
	{
		tmp = *export_head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}



/*
t_token	*create_variable(t_token *head)
{
	
}
*/
t_token	*extract_variable(t_token *head, char **envp)
{
	int	size_env;
	t_token	*new_node;

	while (*envp)
	{
		size_env = 0;
		if (ft_strcmp(*envp, "_=/usr/bin/env") == 0)
			return (head);
		size_env = ft_strlen(*envp);
			new_node = malloc(sizeof(t_token));
			if (!new_node)
				return (NULL);
			new_node->export = malloc(size_env + 1);
			if (!new_node->export)
				return (NULL);
			ft_strncpy(new_node->export, *envp, size_env);
			new_node->export[size_env] = '\0';
			new_node->next = NULL;
			ft_lstadd_back_export(&head, new_node);
			ft_printf("%s\n",new_node->export);
		envp++;
	}
	return (head);
}

void	builtin_export(t_token *head, char **envp)
{
	t_token *current;
	//t_token	*export_head;
	t_token *globais_variables;
	t_token	*tmp;

	current = head->next;
	globais_variables = extract_variable(head, envp);
	tmp = globais_variables;
	
	if (!current)
	{
		while (tmp)
		{
			ft_printf("%s\n",tmp->export);
			tmp = tmp->next;
		}
	}
	
	/*
	else
	{
		export_head = create_variable(head);

	}
	*/
}
