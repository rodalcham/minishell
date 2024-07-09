/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_by_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:56:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/09 14:56:39 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*env_get_by_name(char *name)
{
	int		i;
	char	**env;
	size_t	name_len;

	env = *ft_env();
	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, name_len)
			&& env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}
