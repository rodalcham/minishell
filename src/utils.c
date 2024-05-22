/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/22 13:41:26 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_spc(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	is_op(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	**my_completion_function(const char *text, int start, int end)
{
	char	**matches;

	matches = NULL;
	(void)end;
	if (start == 0 && text[0] == 0)
		rl_attempted_completion_over = 1;
	else if (start == 0 && text[0] == ' ')
		matches = rl_completion_matches(text, rl_completion_entry_function);
	return (matches);
}
