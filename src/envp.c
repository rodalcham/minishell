/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:25:12 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/05 16:23:12 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_free(char **ret)
{
	int	i;

	i = 0;
	if (!ret)
		return ;
	while (ret[i])
		free_t (ret[i++]);
	free_t(ret);
}

char	**ft_make_envp(char **ret)
{
	char	buffer[4096];

	ret[0] = ft_strdup(ft_strjoin("PWD=", getcwd(buffer, sizeof(buffer))));
	if (!ret[0])
	{
		free_t(ret);
		return (0);
	}
	ret[1] = ft_strdup("SHLVL=0");
	if (!ret[1])
	{
		free_t(ret[0]);
		free_t(ret);
		return (0);
	}
	ret[2] = ft_strdup("_=");
	if (!ret[2])
	{
		free_t(ret[0]);
		free_t(ret[1]);
		free_t(ret);
		return (0);
	}
	ret[3] = NULL;
	return (ret);
}

char	**init_env(char **env)
{
	int		i;
	char	**ret;

	i = 0;
	while (env[i])
		i++;
	if (env && env[0])
		ret = (char **)malloc_t(sizeof(char *) * (i + 1));
	else
		ret = (char **)malloc_t(sizeof(char *) * (3 + 1));
	if (!ret)
		return (NULL);
	if (!env || !env[0])
		return (ft_make_envp(ret));
	i = 0;
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		if (!ret[i])
			return (env_free(ret), NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
