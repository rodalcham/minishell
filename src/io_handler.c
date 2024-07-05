/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:16:18 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/05 15:18:41 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	add_input(t_lexer *lex, char **args, int *i)
{
	int	fd;

	if ((lex->input && lex->input->fd < 0)
		|| (lex->output && lex->output->fd < 0) || !args[*i + 1])
		return (0);
	fd = 0;
	(*i)++;
	args[*i] = remove_quotes(args[*i]);
	fd = open(args[*i], O_RDONLY, 0);
	if (fd < 0)
		ft_perror(args[*i], " : No such file or directory.\n", NULL);
	if (!lex->input)
		lex->input = new_file();
	else
		close(lex->input->fd);
	if (!lex->input)
		return (-1);
	set_file(lex->input, args[*i], O_RDONLY, fd);
	return (0);
}

int	add_output(t_lexer *lex, char **args, int *i)
{
	int	fd;
	int	mod;

	if ((lex->input && lex->input->fd < 0)
		|| (lex->output && lex->output->fd < 0) || !args[*i + 1])
		return (0);
	fd = 0;
	if (args[*i][1] == '>')
		mod = (O_WRONLY | O_APPEND | O_CREAT);
	else
		mod = (O_WRONLY | O_TRUNC | O_CREAT);
	(*i)++;
	args[*i] = remove_quotes(args[*i]);
	fd = open(args[*i], mod, PERMISSIONS);
	if (fd < 0)
		ft_perror(args[*i], " : No such file or directory.\n", NULL);
	if (!lex->output)
		lex->output = new_file();
	else
		close(lex->output->fd);
	if (!lex->output)
		return (-1);
	set_file(lex->output, args[*i], mod, fd);
	return (0);
}

int	add_heredoc(t_lexer *lex, char **args, int *i)
{
	int	p_fd[2];
	int	mode;

	if ((lex->input && lex->input->fd < 0)
		|| (lex->output && lex->output->fd < 0) || !args[*i + 1])
		return (0);
	if (pipe(p_fd) < 0)
		return (-5);
	(*i)++;
	mode = has_quotes(args[*i]);
	args[*i] = remove_quotes(args[*i]);
	if (do_heredoc(p_fd[1], args[*i], mode) < 0)
	{
		close(p_fd[0]);
		return (0);
	}
	if (!lex->input)
		lex->input = new_file();
	else
		close(lex->input->fd);
	if (!lex->input)
		return (-1);
	set_file(lex->input, "Heredoc", O_RDONLY, p_fd[0]);
	return (0);
}

int	add_pipe(t_lexer *lex)
{
	int	p_fd[2];

	if (pipe(p_fd) < 0)
		return (-5);
	if (!lex->output)
	{
		lex->output = new_file();
		if (!lex->output)
			return (-1);
		set_file(lex->output, "PIPE", (O_WRONLY | O_TRUNC | O_CREAT), p_fd[1]);
	}
	else
		close(p_fd[1]);
	if (lex->next)
	{
		lex->next->input = new_file();
		if (!lex->next->input)
			return (-1);
		set_file(lex->next->input, "PIPE", O_RDONLY, p_fd[0]);
	}
	return (0);
}
