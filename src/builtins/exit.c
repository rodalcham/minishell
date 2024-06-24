/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:57:54 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/24 12:35:29 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char *line, char **args)
{
	if (args[1] && !args[2])
		*get_exit_status() = ft_atoi(remove_quotes(args[1]));
	free_line(line);
	free_args(args);
	return (*get_exit_status());
}
