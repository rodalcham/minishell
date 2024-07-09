/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:40:17 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/09 14:44:00 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	do_heredoc(int fd, char *eof, int mode)
{
	int		written;
	int		pid;

	if (*get_exit_status() == 130)
		return (0);
	if (!isatty(fileno(stdin)))
		return (heredoc_gnl(fd, eof, mode));
	written = 0;
	signal(SIGINT, exit_130);
	pid = fork();
	if (pid == 0)
		exit (heredoc_child(written, eof, fd, mode));
	else if (pid < 0)
		return (-1);
	else
	{
		waitpid(pid, &written, 0);
		if (written < 0)
			return (-1);
	}
	close(fd);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
