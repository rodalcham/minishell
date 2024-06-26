/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:04:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/25 14:56:00 by lglauch          ###   ########.fr       */
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

void	remove_n_flag(char *line, int *index)
{
	while (line[*index] && line[*index] == '-'
		&& line[*index + 1] == 'n' && is_spc(line[*index + 2]))
	{
		*index += 3;
		remove_n_flag(line, index);
	}
}

char	*transform_correct(char *line, int n)
{
	int		i;
	int		single;
	int		doubl;
	char	*new_str;
	int		j;

	i = 0;
	single = 0;
	doubl = 0;
	j = 0;
	new_str = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i])
	{
		while (is_spc(line[i]) && is_spc(line[i + 1]) && !single && !doubl)
			i++;
		if (n > 0 && line[i] && line[i] == '-' && line[i + 1] == 'n' && is_spc(line[i + 2]))
		{
			remove_n_flag(line, &i);
			n = 0;
		}
		if (line[i] == '\"' && single == 0)
		{
			doubl = !doubl;
			new_str[j++] = line[i++];
		}
		if (line[i] == '\'' && doubl == 0)
		{
			single = !single;
			new_str[j++] = line[i++];
		}
		if ((line[i] == '>' || line[i] == '<' || line[i] == '|') && !single && !doubl)
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
	int		skip_n;

	i = 1;
	newline = 1;
	skip_n = 0;
	if (lexer->cmd[i] && !ft_strcmp(lexer->cmd[i], "-n"))
	{
		newline = 0;
		skip_n = 1;
		i++;
	}
	line = *last_line();
	line += 4;
	while (is_spc(*line))
		line++;
	line = transform_correct(line, skip_n);
	if (line && remove_quotes(line))
		printf ("%s", line);
	if (newline && printf("\n"))
		return (0);
	return (0);
}
