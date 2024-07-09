/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:04:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/09 15:49:34 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_n_flag(char *str)
{
	size_t	i;

	i = 0;
	if (!str || str[0] != '-')
		return (0);
	if (str[i] == '-' && str [i + 1] == 0)
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_command(t_lexer *lexer)
{
	int		i;
	int		j;
	int		newline;
	char	**cmd;

	i = 0;
	newline = 1;
	cmd = lexer->cmd;
	while (cmd[++i] && is_n_flag(cmd[i]))
		newline = 0;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][0] == '~' && (!cmd[i][1] || cmd[i][1] == '/')
			&& env_pos(*ft_env(), "HOME") >= 0 && ++j)
			printf("%s", env_get_by_name("HOME"));
		printf("%s", &cmd[i][j]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
