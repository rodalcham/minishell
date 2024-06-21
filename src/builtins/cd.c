/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:13:59 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/21 11:56:46 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_command(t_lexer *lexer)
{
	char	*path;

	path = env_get_by_name("HOME");
	if (lexer->cmd[1] == NULL)
	{
		if (ft_strncmp(path, "", 1) == 0)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		else if (chdir(path) == -1)
		{
			printf("cd: %s: No such file or directory\n", path);
			return (1);
		}
	}
	else if (chdir(lexer->cmd[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", lexer->cmd[1]);
		return (1);
	}
	return (0);
}
