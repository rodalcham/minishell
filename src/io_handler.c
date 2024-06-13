/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:16:18 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/13 11:05:52 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_input(t_lexer *lex, char **args, int *i)
{
	int	fd;

	fd = 0;
	(*i)++;
	if (!lex->input)
		lex->input = new_file(lex->input);
	else
		close(*lex->input->fd);
	fd = open(args[*i], READ);
	if (fd < 0)
		printf("\nFREE AND RETURN\n");
	set_file(lex->input, args[*i], READ, fd);
}

void	add_output(t_lexer *lex, char **args, int *i)
{
	int	fd;
	int mod;

	fd = 0;
	(*i)++;
	if (args[*i][1] == '>')
		mod = APPEND;
	else
		mod = WRITE;
	if (!lex->output)
		lex->output = new_file(lex->output);
	else
		close(*lex->input->fd);
	fd = open(args[*i], mod, PERMISSIONS);
	if (fd < 0)
		printf("\nFREE AND RETURN\n");
	set_file(lex->output, args[*i], mod, fd);
}

void	here_doc(t_lexer *lex, char **args, int *i)
{
	if (lex && args && i)
		printf("\nMISSING: HEREDOC\n");
}

void	add_pipe(t_lexer *lex)
{
	int	p_fd[2];

	if (lex->output)
		return ;
	if (pipe(p_fd) < 0)
		printf("\nFREE AND RETURN\n");
	lex->output = new_file(lex->output);
	set_file(lex->output, "PIPE", WRITE, p_fd[1]);
	if (lex->next)
	{
		lex->next->input = new_file(lex->next->input);
		set_file(lex->next->input, "PIPE", READ, p_fd[0]);
	}
}
