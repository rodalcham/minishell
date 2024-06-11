/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:53:59 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/11 14:41:27 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	ft_check_commands(t_lexer *lexer)
// {
// 	if (lexer->cmd)
// 	{
// 		if (ft_strncmp(lexer->cmd[0], "echo", ft_strlen("echo")) == 0)
// 			return (1);
// 		if (ft_strncmp(lexer->cmd[0], "cd", ft_strlen("cd")) == 0)
// 			return (2);
// 		if (ft_strncmp(lexer->cmd[0], "pwd", ft_strlen("pwd")) == 0)
// 			return (3);
// 		if (ft_strncmp(lexer->cmd[0], "export", ft_strlen("export")) == 0)
// 			return (4);
// 		if (ft_strncmp(lexer->cmd[0], "unset", ft_strlen("unset")) == 0)
// 			return (5);
// 		if (ft_strncmp(lexer->cmd[0], "env", ft_strlen("env")) == 0)
// 			return (6);
// 		if (ft_strncmp(lexer->cmd[0], "exit", ft_strlen("exit")) == 0)
// 			return (7);
// 	}
// 	return (0);
// }

// int	call_functions(t_lexer *lexer)
// {
// 	int	i;
// 	int	exit_code;

// 	i = ft_check_commands(lexer);
// 	if (i == 1)
// 		exit_code = echo_command(lexer);
// 	if (i == 2)
// 		exit_code = cd_command(lexer);
// 	if (i == 3)
// 		exit_code = pwd_command(lexer);
// 	if (i == 4)
// 		exit_code = export_command(lexer);
// 	if (i == 5)
// 		exit_code = unset_command(lexer);
// 	if (i == 6)
// 		exit_code = env_command(lexer);
// 	if (i == 7)
// 		exit_code = exit_command(lexer);
// 	return (exit_code);
// }
