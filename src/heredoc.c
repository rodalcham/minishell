/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:31:18 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/17 12:11:37 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{

}

int	do_heredoc(int fd, char *eof)
{
	int		written;
	char	*line;

	written = 0;
	line = readline("> ");
	while (written > 0 && line && ft_strcmp(line, eof))
	{
		written = write(fd, line, ft_strlen(line));
		if (written < 0 || write(fd, "\n", 1) < 0)
		{
			printf("Heredoc : Failed to write.\n");
			break ;
		}
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	if (written < 0)
		return (-1);
	return (0);
}
