/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hof_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:10:24 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/07 15:10:25 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmp(t_token_type type_a, t_token_type type_b)
{
	if (type_a == type_b)
		return (1);
	return (0);
}
