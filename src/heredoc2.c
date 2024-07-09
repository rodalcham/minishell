/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:31:18 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/09 14:44:25 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*rm_nl(char *line);

void	custom_handler(int signal)
{
	(void)signal;
	printf("\n");
	*get_exit_status() = 130;
	exit(130);
}

void	exit_130(int signal)
{
	(void)signal;
	*get_exit_status() = 130;
}

char	*heredoc_gl(int mode)
{
	char	*line;

	line = take_in("> ");
	if (!mode)
		line = expand_tokens(line, 1);
	return (line);
}

int	heredoc_child(int written, char *eof, int fd, int mode)
{
	char	*line;

	g_signal = 1;
	signal(SIGINT, custom_handler);
	written = 1;
	line = heredoc_gl(mode);
	if (!line)
		return (-1);
	while (written >= 0 && line && ft_strcmp(line, eof))
	{
		written = write(fd, line, ft_strlen(line));
		if (written < 0 || write(fd, "\n", 1) < 0)
		{
			write(2, "Heredoc : Failed to write.\n", 27);
			break ;
		}
		free_t(line);
		line = heredoc_gl(mode);
		if (!line)
			return (-1);
	}
	if (line)
		free_t(line);
	close(fd);
	return (written);
}

int	heredoc_gnl(int fd, char *eof, int mode)
{
	char	*line;
	int		written;

	written = 1;
	line = heredoc_gl(mode);
	while (line && ft_strcmp(line, eof) && written >= 0)
	{
		written = write(fd, line, ft_strlen(line));
		if (written < 0 || write(fd, "\n", 1) < 0)
		{
			write(2, "Heredoc : Failed to write.\n", 27);
			close(fd);
			return (free_t(line), -1);
		}
		if (line)
			free_t(line);
		line = heredoc_gl(mode);
	}
	close(fd);
	return (0);
}
