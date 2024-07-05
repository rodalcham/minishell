/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:23:04 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/05 16:23:50 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lexer(t_lexer *head)
{
	t_lexer	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		if (temp->cmd)
			free_t(temp->cmd);
		if (temp->input)
			free_t(temp->input);
		if (temp->output)
			free_t(temp->output);
		if (temp->path)
			free_t(temp->path);
		head = head->next;
		free_t(temp);
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free_t(args[i]);
		i++;
	}
	free_t(args);
}

void	free_line(char *line)
{
	if (!line)
		return ;
	free_t(line);
}

void	free_all(char *line, char **args, t_lexer *head, int errno)
{
	free_line(line);
	free_args(args);
	free_lexer(head);
	if (errno)
		ft_error(errno);
}
