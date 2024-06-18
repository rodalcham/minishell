/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:15 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/18 13:20:52 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_list(t_envp *envp_list, char *name)
{
	t_envp	*tmp;
	t_envp	*prev;

	tmp = NULL;
	prev = envp_list;
	while (envp_list != NULL && ft_strncmp(envp_list->name, name,
			ft_strlen(envp_list->name)) != 0)
	{
		prev = envp_list;
		envp_list = envp_list->next;
	}
	if (envp_list == NULL)
		return ;
	tmp = envp_list;
	prev->next = envp_list->next;
	free(tmp->value);
	free(tmp->name);
	free(tmp);
}

void	remove_envp(char *name)
{
	t_envp	*envp_list;
	t_envp	*tmp;

	tmp = NULL;
	envp_list = *get_envp();
	if (envp_list == NULL)
		return ;
	if (ft_strncmp(envp_list->name, name, ft_strlen(envp_list->name)) == 0)
	{
		tmp = envp_list;
		*get_envp() = envp_list->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return ;
	}
	check_list(envp_list, name);
}

int	unset_command(t_lexer *lexer)
{
	char	*name;

	name = lexer->cmd[1];
	if (!name)
	{
		printf("\n");
		return (0);
	}
	if (!(ft_strncmp(env_get_by_name(name), "", ft_strlen(name)) == 0))
		remove_envp(name);
	return (0);
}
