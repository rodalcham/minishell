/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:28 by leo               #+#    #+#             */
/*   Updated: 2024/06/23 11:38:53 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_len(char **env)
{
	int i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i + 1);
}

int	envp_add(char *cmd, char **env)
{
	char	**new;
	char	*eq;
	int		i;

	new = (char **)malloc(sizeof(char *) * (env_len(env) + 1));
	if (!new)
		return (-1);
	eq = ft_strchr(cmd, '=');
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
		return (free(new), -1);
	new[++i] = NULL;
	*ft_env() = new;
	return (0);
}

void	envp_update_value(char *name, char *value)
{
	t_envp	*envp_list;

	envp_list = *get_envp();
	while (envp_list != NULL)
	{
		if (ft_strncmp(envp_list->name, name, ft_strlen(envp_list->name)) == 0)
		{
			free(envp_list->value);
			envp_list->value = ft_strdup(value);
			break ;
		}
		envp_list = envp_list->next;
	}
}

int	export_command(t_lexer *lexer)
{
	char	*cmd;
	char	*eq;

	cmd = lexer->cmd[1];
	if (!cmd)
	{
		printf("export : INVALID USAGE\n");
		return (0);
	}
	eq = ft_strchr(cmd, '=');
	if (eq && *(eq - 1) == '-')
	{
		printf("export : '%s' : not a valid identifier\n", cmd);
		return (0);
	}
	if (env_get_by_name(cmd)[0]) //not working
		printf("ENV : %s\n", env_get_by_name(cmd));
	else
		if (envp_add(cmd, *ft_env()) < 0)
			return (-1);
	return (0);
}
