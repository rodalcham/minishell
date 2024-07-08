/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:15 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/08 21:50:36 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_cmp(char *s1, char *s2);

void	do_unset(char **env, char *str)
{
	int		i;

	i = -1;
	if (!env)
		return ;
	while (env[++i])
	{
		if (!env_cmp(env[i], str))
		{
			free_t(env[i]);
			while (env[++i])
				env[i - 1] = env[i];
			env[i - 1] = NULL;
			break ;
		}
	}
}

int	unset_command(t_lexer *temp)
{
	char	**env;
	int		j;

	env = *ft_env();
	j = 0;
	while (temp->cmd[++j])
	{
		if (!temp->cmd[j])
			return (0);
		do_unset(env, temp->cmd[j]);
	}
	*get_exit_status() = 0;
	return (0);
}
