/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:15 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/07 10:56:33 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_cmp(char *s1, char *s2);

int	unset_command(t_lexer *temp)
{
	char	**env;
	int		i;
	int		j;

	env = *ft_env();
	j = 0;
	while (temp->cmd[++j])
	{
		if (!temp->cmd[j])
			return (0);
		i = -1;
		while (env[++i])
		{
			if (!env_cmp(env[i], temp->cmd[j]))
			{
				free_t(env[i]);
				while (env[++i])
					env[i - 1] = env[i];
				env[i - 1] = NULL;
				break;
			}
		}
	}
	return (0);
}
