/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:25:08 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/08 17:48:31 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_has_value(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=')
		i++;
	i++;
	if (str[i] == 0)
		return (0);
	return (1);
}

int	env_command(t_lexer *lexer)
{
	char	**list;
	int		i;

	if (lexer->cmd[1])
		return (0);
	list = *ft_env();
	if (list == NULL)
		return (1);
	i = 0;
	while (list[i])
	{
		printf("%s\n", list[i]);
		i++;
	}
	return (0);
}
