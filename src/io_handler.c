/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:16:18 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/11 12:07:55 by rchavez          ###   ########.fr       */
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
	fd = open(args[*i], READ);
	if (fd < 0)
		printf("\nFREE AND RETURN\n");
	set_file(lex->input, args[*i], fd, READ);
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
	fd = open(args[*i], mod, PERMISSIONS);
	if (fd < 0)
		printf("\nFREE AND RETURN\n");
	set_file(lex->output, args[*i], fd, mod);
}

void	here_doc(t_lexer *lex, char **args, int *i)
{
	if (lex && args && i)
		printf("\nMISSING: HEREDOC\n");
}
