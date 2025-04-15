/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:19:12 by alda-sil          #+#    #+#             */
/*   Updated: 2025/04/14 18:54:07 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_pwd()
{
	char	buf[100];
	
	getcwd(buf, 100);
	ft_printf("%s\n", buf);
}

int	main()
{
	builtin_pwd();
	return (0);
}