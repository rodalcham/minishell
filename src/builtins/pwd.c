/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:05 by leo               #+#    #+#             */
/*   Updated: 2024/06/12 13:35:15 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_command(t_lexer *lexer)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("pwd: error retrieving current directory\n");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
