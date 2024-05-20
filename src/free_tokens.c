/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:15:27 by rchavez           #+#    #+#             */
/*   Updated: 2024/05/20 15:55:49 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(t_lexer *tokens, char **args, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = count_lex(line);
	free(line);
	while (i < j)
	{
		free(tokens[i].cmd);
		free(tokens[i].ops);
		// free(tokens[i].path);
		i++;
	}
	free(tokens);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
