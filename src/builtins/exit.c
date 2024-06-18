/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:57:54 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/18 12:38:57 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(char *line, char **args)
{
	if (args[1])
		*get_exit_status() = ft_atoi(args[1]);
	free_line(line);
	free_args(args);
}
