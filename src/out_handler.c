/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:47:07 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/11 14:40:50 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_get_fd(char *op, char *input)
{
	int	fd;

	fd = 0;
	if (ft_strncmp(op, ">", 1) == 0)
		fd = open(input, O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONS);
	else if (ft_strncmp(op, ">>", 2) == 0)
		fd = open(input, O_WRONLY | O_CREAT | O_APPEND, PERMISSIONS);
	return (fd);
}

void	out_to_file(char *quitter, char *op)
{
	char	*input;
	int		fd;

	while (1)
	{
		input = readline("");
		if (!input)
		{
			printf("Readline failed in out_function\n");
			break ;
		}
		if (ft_strncmp(input, quitter, ft_strlen(quitter)) == 0)
		{
			free (input);
			break ;
		}
		fd = ft_get_fd(op, input);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		close(fd);
		free(input);
	}
}
