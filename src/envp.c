/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:25:12 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/28 13:42:01 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_envp(t_envp *head)
{
	printf("free nodes");
	t_envp	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

char	*ft_envp_get_value(char *envp)
{
	int		i;
	int		j;
	int		len;
	char	*value;

	value = NULL;
	i = 0;
	j = 0;
	if (!envp)
		return (0);
	while (envp[i] != '=' && envp[i] != 0)
		i++;
	while (envp[j] != 0)
		j++;
	if (envp[i] == 0)
		return (NULL);
	len = j - i;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	j = 0;
	while (envp[++i])
		value[j++] = envp[i];
	value[j] = 0;
	return (value);
}

char	*ft_envp_get_name(char *envp)
{
	char	*name;
	int		i;

	name = NULL;
	i = 0;
	if (!envp)
		return (0);
	while (envp[i] != '=' && envp[i] != 0)
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (envp[i] != '=' && envp[i] != 0)
	{
		name[i] = envp[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

t_envp	*ft_create_envp(char **envp)
{
	t_envp	*head;
	t_envp	*current;
	t_envp	*new_node;
	int		j;

	j = 0;
	head = NULL;
	current = NULL;
	while (envp[j])
	{
		new_node = malloc(sizeof(t_envp));
		new_node->name = ft_envp_get_name(envp[j]);
		new_node->value = ft_envp_get_value(envp[j]);
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		j++;
	}
	return (head);
}
