/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:28 by leo               #+#    #+#             */
/*   Updated: 2024/06/17 11:43:05 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	envp_add(char *name, char *value)
{
	t_envp	*new_node;
	t_envp	*envp_list;

	new_node = malloc(sizeof(t_envp));
	if (new_node == NULL)
	{
		printf("Malloc error in envp_add");
		return ;
	}
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	envp_list = *get_envp();
	if (envp_list == NULL)
	{
		*get_envp() = new_node;
		return ;
	}
	while (envp_list->next != NULL)
	{
		envp_list = envp_list->next;
	}
	envp_list->next = new_node;
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
	char	*new;

	cmd = lexer->cmd[1];
	new = ft_strchr(cmd, '=');
	if (new != NULL)
	{
		*new = 0;
		new++;
	}
	if (env_get_by_name(cmd))
	{
		envp_update_value(cmd, new);
	}
	else
	{
		envp_add(cmd, new);
	}
	return (0);
}
