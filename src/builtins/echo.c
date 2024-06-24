/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:04:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/24 13:28:36 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	echo_command(t_lexer *lexer)
// {
// 	int	i;
// 	int	newline;

// 	i = 1;
// 	newline = 1;
// 	if (lexer->cmd[i] && !ft_strcmp(lexer->cmd[i], "-n"))
// 	{
// 		newline = 0;
// 		i++;
// 	}
// 	while (lexer->cmd[i])
// 	{
// 		while (lexer->cmd[i])
// 		{
// 			if (printf("%s", lexer->cmd[i++]) == -1)
// 				return (1);
// 			if (lexer->cmd[i])
// 			{
// 				if (printf(" ") == -1)
// 					return (1);
// 			}
// 		}
// 	}
// 	if (newline && printf("\n"))
// 		return (0);
// 	return (0);
// }

char	*transform_correct(char *line)
{
	int		i;
	int		in_single_quotes;
	int		double_quotes;
	char	*new_str;
	int		j;

	i = 0;
	in_single_quotes = 0;
	double_quotes = 0;
	j = 0;
	new_str = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i])
	{
		while (is_spc(line[i]) && is_spc(line[i + 1]) && !in_single_quotes && !double_quotes)
			i++;
		if (line[i] == '\"' && in_single_quotes == 0)
			double_quotes = !double_quotes;
		else if (line[i] == '\'' && double_quotes == 0)
			in_single_quotes = !in_single_quotes;
		else if ((line[i] == '>' || line[i] == '<' || line[i] == '|') && !in_single_quotes && !double_quotes)
			{
				if (line[i] == '|')
				{
					line[i] = 0;
					break ;
				}
				while (line[i] != 0 && !is_spc(line[i]))
					i++;
			}
		else
			new_str[j++] = line[i];
		i++;
	}
	new_str[j] = 0;
	return (new_str);
}

int	echo_command(t_lexer *lexer)
{
	int		i;
	int		newline;
	char	*line;

	i = 1;
	newline = 1;
	if (lexer->cmd[i] && !ft_strcmp(lexer->cmd[i], "-n"))
	{
		newline = 0;
		i++;
	}
	line = *last_line();
	line += 4;
	while (is_spc(*line))
		line++;
	line = transform_correct(line);
	if (line && remove_quotes(line))
		printf ("%s", line);
	if (newline && printf("\n"))
		return (0);
	return (0);
}
