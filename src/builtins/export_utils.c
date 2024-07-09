/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:56:51 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/09 15:11:28 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_len(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i + 1);
}

int	envp_add(char **env, char *cmd, int pos, char *eq)
{
	char	**new;
	int		i;

	new = (char **)malloc_t(sizeof(char *) * (env_len(env) + 1));
	if (!new)
		return (-1);
	if (eq && eq != cmd && *(eq - 1) == '+')
	{
		eq--;
		while (*(++eq))
			*(eq - 1) = *(eq);
		*(eq - 1) = '\0';
	}
	i = -1;
	while (env[++i])
		new[i] = env[i];
	new[i] = ft_strdup(cmd);
	if (!new[i])
		return (free_t(new), -1);
	new[++i] = NULL;
	*ft_env() = new;
	if (pos >= 0)
		free_t(env);
	return (*get_exit_status() = 0);
}

int	envp_update_value(char **env, char *cmd, int pos, char *eq)
{
	char	*new;

	new = NULL;
	if (eq && eq != cmd && *(eq - 1) == '+' && *(eq + 1))
		new = ft_strjoin(env[pos], (eq + 1));
	else if (eq)
		new = ft_strdup(cmd);
	else
		return (0);
	if (!new)
		return (-1);
	free_t(env[pos]);
	env[pos] = new;
	return (*get_exit_status() = 0);
}

int	declare_usage(void)
{
	char	**env;
	int		i;
	size_t	j;

	env = *ft_env();
	i = -1;
	while (env && env[++i])
	{
		j = 0;
		printf("declare -x ");
		while (env[i][j] && env[i][j] != '=')
			printf("%c", env[i][j++]);
		if (env[i][j])
		{
			printf("=");
			j++;
		}
		if (env[i][j])
			printf("\"%s\"", &env[i][j]);
		printf("\n");
	}
	*get_exit_status() = 0;
	return (0);
}
