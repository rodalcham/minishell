/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:25:08 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/23 09:25:43 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_command(void)
{
	char	**list;
	int		i;

	list = *ft_env();
	if (list == NULL)
		return (1);
	i = 0;
	while (list[i])
	{
		printf("%s\n", list[i]);
		i++;
	}
	return (0);
}
