/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:25:08 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/17 12:29:59 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_command(t_lexer *lexer)
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
