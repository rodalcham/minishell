/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:31:18 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/28 11:40:36 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	heredoc_child(int written, char *eof, int fd)
{
	char	*line;

	signal(SIGINT, exit);
	written = 1;
	line = readline("> ");
	while (written >= 0 && line && ft_strcmp(line, eof))
	{
		written = write(fd, line, ft_strlen(line));
		if (written < 0 || write(fd, "\n", 1) < 0)
		{
			perror("Heredoc : Failed to write.\n");
			break ;
		}
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	return(written);
}

int	do_heredoc(int fd, char *eof)
{
	int		written;
	int 	pid;

	written = 0;
	// signal(SIGINT, SIGUSR1);
	pid = fork();
	if (pid == 0)
		exit (heredoc_child(written, eof, fd));
	else if (pid < 0)
		return (-1);
	else
	{
		waitpid(pid, &written, 0);
		if (written < 0)
			return (-1);
	}
	close(fd);
	return (0);
}
