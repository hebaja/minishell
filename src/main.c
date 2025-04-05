/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:20:37 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/03 20:20:41 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/history.h>

t_token_type	define_type(char *value)
{
	if (ft_strncmp(value, "|", 2) == 0)
		return (PIPE);
	else if (ft_strncmp(value, ">>", 3) == 0)
		return (APPEND);
	else if (ft_strncmp(value, "<<", 3) == 0)
		return (HEREDOC);
	else if (ft_strncmp(value, ">", 2) == 0)
		return (REDIRECT_OUT);
	else if (ft_strncmp(value, "<", 2) == 0)
		return (REDIRECT_IN);
	return (WORD);
}

void	token_clear(t_token *token)
{
	if (!token)
		return ;
	token->next = NULL;
	free(token->value);
	free(token);
	token = NULL;
}

void	token_lst_clear(t_token **token_lst_head)
{
	t_token	*token;
	t_token	*token_tmp;

	token = *token_lst_head;
	if (token)
	{
		token_tmp = token;
		token = token->next;
		token_clear(token_tmp);
	}
	*token_lst_head = NULL;
}

t_token	*token_lst_last(t_token *token_lst)
{
	t_token	*current_token;

	current_token = token_lst;
	while (current_token)
	{
		if (current_token->next == NULL)
			break ;
		current_token = current_token->next;
	}
	return (current_token);
}

void	token_lst_add_back(t_token **token_lst_head, t_token *token)
{
	if (*token_lst_head == NULL)
		*token_lst_head = token;
	else
		token_lst_last(*token_lst_head)->next = token;
}

t_token	*token_build(char *value_start, size_t size)
{
	t_token	*token;
	char	*value;

	token = (t_token *)malloc(sizeof(t_token));
	value = (char *)malloc(sizeof(char) * (size + 1));
	if (!token || !value)
		return (NULL);
	ft_strlcpy(value, value_start, size + 1);
	token->value = value;
	token->type = define_type(value);
	token->next = NULL;
	return (token);
}

int	token_lst_build(t_token **tokens_head, char *value)
{
	t_token	*token;
	char	*value_start;
	size_t		size;

	value_start = value;
	size = 0;
	while (*value)
	{
		while (*value && !ft_isspace(*value))
		{
			value++;
			size++;
		}
		if (tokens_head == NULL || *tokens_head == NULL)
		{
			*tokens_head = token_build(value_start, size);
			if (!token)
				return (0);
		}
		else
		{
			token = token_build(value_start, size);
			if (!token)
			{
				token_lst_clear(tokens_head);
				return (0);
			}
			token_lst_add_back(tokens_head, token);
		}
		while (*value && ft_isspace(*value))
			value++;
		if (*value)
			value_start = value;
		size = 0;
	}
	return (1);
}

char	*print_token_type(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == REDIRECT_IN) 
		return ("REDIRECT_IN");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	return ("");
}

void	print_tokens(t_token *tokens_head)
{
	t_token	*current_token;

	current_token = tokens_head;
	while(current_token)
	{
		printf("value = %s, type = %s, next = %p\n", current_token->value,
			print_token_type(current_token->type),
			current_token->next);
		current_token = current_token->next;
	}
}

int	main()
{
	char	*input;
	t_token	*tokens_head;

	tokens_head = NULL;
	using_history();
	input = readline(TERMINAL_PROMPT);
	while (input)
	{
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		if (input)
			add_history(input);
		token_lst_build(&tokens_head, input);
		print_tokens(tokens_head);
		free(input);
		token_lst_clear(&tokens_head);
		input = readline(TERMINAL_PROMPT);
	}
	if (tokens_head)
		token_lst_clear(&tokens_head);
	return (0);
}
