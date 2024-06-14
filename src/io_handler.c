/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:16:18 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/14 14:59:53 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	add_input(t_lexer *lex, char **args, int *i)
{
	int	fd;

	fd = 0;
	(*i)++;
	fd = open(args[*i], READ);
	if (fd < 0)
		printf("%s : No such file or directory.\n", args[*i]);
	if (!lex->input)
		lex->input = new_file();
	else
		close(lex->input->fd);
	if (!lex->input)
		return (-1);
	set_file(lex->input, args[*i], READ, fd);
	return (0);
}

int	add_output(t_lexer *lex, char **args, int *i)
{
	int	fd;
	int	mod;

	fd = 0;
	(*i)++;
	if (args[*i][1] == '>')
		mod = APPEND;
	else
		mod = WRITE;
	fd = open(args[*i], mod, PERMISSIONS);
	if (fd < 0)
		printf("%s : No such file or directory.\n", args[*i]);
	if (!lex->output)
		lex->output = new_file();
	else
		close(lex->input->fd);
	if (!lex->output)
		return (-1);
	set_file(lex->output, args[*i], mod, fd);
	return (0);
}

int	here_doc(t_lexer *lex, char **args, int *i)
{
	if (lex && args && i)
		printf("\nMISSING: HEREDOC\n");
	return (0);
}

int	add_pipe(t_lexer *lex)
{
	int	p_fd[2];

	if (lex->output)
		return (0);
	if (pipe(p_fd) < 0)
		return (-5);
	lex->output = new_file();
	if (!lex->output)
		return (-1);
	set_file(lex->output, "PIPE", WRITE, p_fd[1]);
	if (lex->next)
	{
		lex->next->input = new_file();
		if (!lex->next->input)
			return (-1);
		set_file(lex->next->input, "PIPE", READ, p_fd[0]);
	}
	return (0);
}
