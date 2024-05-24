/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:16:14 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/05/24 09:55:48 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(t_lexer *tokens, char **args, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = count_lex(line);
	while (i < j)
	{
		free(tokens[i].cmd);
		free(tokens[i].ops);
		free(tokens[i].path);
		i++;
	}
	free(tokens);
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	free(line);
}

void	free_fail(t_lexer *tokens, char **args, char *line, int pos)
{
	int	i;

	i = -1;
	free(line);
	while(args[++i])
		free(args[i]);
	free(args);
	i = 0;
	while (i <= pos)
	{
		if (tokens[i].cmd)
		{
			free(tokens[i].cmd);
			if (tokens[i].ops)
				free(tokens[i].ops);
		}
		if (tokens[i].path)
			free(tokens[i].path);
		i++;
	}
	if (tokens)
		free(tokens);
	ft_error(-1);
}
