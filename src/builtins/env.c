/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:25:08 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/17 13:00:02 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_command(void)
{
	t_envp	*list;

	list = *get_envp();
	if (list == NULL)
		return (1);
	while (list != NULL)
	{
		printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
	return (0);
}
