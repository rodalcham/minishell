/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:55 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/11 12:05:47 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file	*new_file(t_file *head)
{
	t_file	*ret;
	t_file	*temp;

	ret = (t_file *)malloc(sizeof(t_file));
	if (!ret)
		printf("\nFREE AND RETURN\n");
	ret->next = NULL;
	if (!head)
		return (ret);
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp-> next = ret;
	return (head);
}

void	set_file(t_file *head, char *file_n, int mode_n, int fd_n)
{
	t_file *file;

	file = head;
	while (file->next)
		file = file->next;
	file->filename = file_n;
	file->mode = mode_n;
	file->fd = fd_n;
}