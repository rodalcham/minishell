/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:53:59 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/11 12:11:23 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_commands(t_lexer *lexer)
{
	int	i;

	if (lexer->cmd)
	{
		if (ft_strncmp(lexer->cmd[0], "echo", ft_strlen("echo")) == 0)
			return ("echo");
		if (ft_strncmp(lexer->cmd[0], "cd", ft_strlen("cd")) == 0)
			return ("cd");
		if (ft_strncmp(lexer->cmd[0], "pwd", ft_strlen("pwd")) == 0)
			return ("pwd");
		if (ft_strncmp(lexer->cmd[0], "export", ft_strlen("export")) == 0)
			return ("export");
		if (ft_strncmp(lexer->cmd[0], "unset", ft_strlen("unset")) == 0)
			return ("unset");
		if (ft_strncmp(lexer->cmd[0], "env", ft_strlen("env")) == 0)
			return ("env");
		if (ft_strncmp(lexer->cmd[0], "exit", ft_strlen("exit")) == 0)
			return ("exit");
	}
	return (NULL);
}
