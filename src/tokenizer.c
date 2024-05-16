/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:48:06 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/15 13:27:20 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_operator(char *line)
{
	int	i;

	i = 0;
	if (((line[i] == '<') && (line[i + 1] == '<'))
		|| ((line[i] == '>') && (line[i + 1] == '>')))
		return (2);
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (1);
	return (0);
}

int	is_doubleoperator(char *line)
{
	if (ft_strncmp(line, "<<", 2) == 0)
		return (1);
	if (ft_strncmp(line, ">>", 2) == 0)
		return (1);
	return (0);
}

char	**tokenizer(char *line)
{
	char	**tokens;
	int		i;
	int		j;
	int		x;
	char	c;

	tokens = calloc(1, sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	x = 0;
	while (line[i] != 0)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == 0)
			break ;
		tokens = ft_realloc (tokens, (j + 1) * sizeof(char *));
		if (!tokens)
		{
			printf("realloc failed in tokens");
			return (NULL);
		}
		if (line[i] == '"' || line[i] == '\'')
		{
			c = line[i];
			tokens[j] = malloc(2 * sizeof(char));
			if (!tokens[j])
			{
				printf("problem with malloc in tokenizer");
				return (0);
			}
			tokens[j][x++] = line[i++];
			while (line[i])
			{
				tokens[j][x++] = line[i];
				tokens[j] = ft_realloc(tokens[j], (x + 2) * sizeof(char)); //write own realloc
				if (!tokens[j])
				{
					printf("problem with malloc in tokenizer");
					return (0);
				}
				if (line[i] == c)
				{
					i++;
					break ;
				}
				i++;
			}
			tokens[j][x] = 0;
		}
		else if ((is_operator(line + i)) != 0)
		{
			tokens[j] = malloc(sizeof(char));
			if (is_operator(line + i) == 2)
			{
				tokens[j][x++] = line[i++];
				tokens[j] = ft_realloc(tokens[j], (x + 2) * sizeof(char));
				if (!tokens[j])
				{
					printf("problem with malloc in tokenizer");
					return (0);
				}
				tokens[j][x++] = line[i++];
				tokens[j] = ft_realloc(tokens[j], (x + 2) * sizeof(char));
				if (!tokens[j])
				{
					printf("problem with malloc in tokenizer");
					return (0);
				}
			}
			else if (is_operator(line + i) == 1)
			{
				tokens[j][x++] = line[i++];
				tokens[j] = ft_realloc(tokens[j], (x + 2) * sizeof(char));
				if (!tokens[j])
				{
					printf("problem with malloc in tokenizer");
					return (0);
				}
			}
			tokens[j][x] = 0;
		}
		else if (line[i] != ' ')
		{
			tokens[j] = malloc(sizeof(char));
			if (!tokens[j])
			{
				printf("problem with malloc in tokenizer");
				return (0);
			}
			while (line[i] != ' ' && line[i] != 0 && is_operator(line + i) == 0)
			{
				tokens[j][x++] = line[i++];
				tokens[j] = ft_realloc(tokens[j], (x + 2) * sizeof(char));
				if (!tokens[j])
				{
					printf("problem with malloc in tokenizer");
					return (0);
				}
			}
			tokens[j][x] = 0;
		}
		j++;
		x = 0;
	}
	tokens[j] = NULL;
	return (tokens);
}
//error checking ->error messages

//https://github.com/toni-schmitt/minishell#the-basic-functionalities-of-the-project