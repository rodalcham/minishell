/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:13:59 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/28 11:44:28 by rchavez          ###   ########.fr       */
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
			perror("cd: HOME not set\n");
		else if (chdir(path) == -1)
			ft_perror("cd: ", path, ": No such file or directory\n");
		return (1);
	}
	else if (chdir(lexer->cmd[1]) == -1)
	{
		ft_perror("cd: ", lexer->cmd[1], ": No such file or directory\n");
		return (1);
	}
	return (0);
}
