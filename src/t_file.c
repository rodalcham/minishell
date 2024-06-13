/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:55 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/13 11:05:46 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file	*new_file()
{
	t_file	*ret;

	ret = (t_file *)malloc(sizeof(t_file));
	if (!ret)
		printf("\nFREE AND RETURN\n");
	ret->fd = (int *)malloc(sizeof(int));
	if (!ret->fd)
	{
		free(ret);
		printf("\nFREE AND RETURN\n");
	}
	*ret->fd = 0;
	return (ret);
}

void	set_file(t_file *file, char *file_n, int mode_n, int fd_n)
{
	file->filename = file_n;
	file->mode = mode_n;
	*(file->fd) = fd_n;
}