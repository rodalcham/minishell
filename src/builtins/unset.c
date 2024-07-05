/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:15 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/05 16:25:21 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			if (!ft_strncmp(env[i], temp->cmd[j], ft_strlen(temp->cmd[j])))
			{
				free_t(env[i]);
				while (env[++i])
					env[i - 1] = env[i];
				env[i - 1] = NULL;
				break ;
			}
		}
	}
	return (0);
}
