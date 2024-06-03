/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/03 17:18:12 by lglauch          ###   ########.fr       */
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

char	*make_unclosed_quotes(char *str, int double_quotes, int single)
{
	char	*new_input;
	char	*new_str;
	// char	*tmp_str;
	int		i;

	new_str = malloc(sizeof(char) * ft_strlen(str) + 2);
	ft_strcpy(new_str, str);
	ft_strlcat(new_str, "\n", ft_strlen(new_str) + 2);
	while (double_quotes == 1 || single == 1)
	{
		new_input = readline("> ");
		if (!new_input)
			return (NULL);
		new_str = realloc(new_str, sizeof(char) * (ft_strlen(new_str)
					+ ft_strlen(new_input) + 3));
		if (!new_str)
		{
			free(new_input);
			return (NULL);
		}
		ft_strlcat(new_str, new_input, ft_strlen(new_str)
			+ ft_strlen(new_input) + 2);
		ft_strlcat(new_str, "\n", ft_strlen(new_str) + 2);
		i = 0;
		while (new_input[i])
		{
			if (new_input[i] == '"' && double_quotes == 1)
			{
				double_quotes = 0;
			}
			else if (new_input[i] == '\'' && single == 1)
			{
				single = 0;
			}
			// else if (new_input[i] == '$' && double_quotes == 1)
			// {
			// 	tmp_str = new_str;
			// 	new_str = expand_tokens(tmp_str + i, tmp_str, i);
			// }
			i++;
		}
		free(new_input);
	}
	return (new_str);
}

char	*handle_unclosed_quotes(char *str)
{
	int	i;
	int	single;
	int	double_quotes;

	i = 0;
	single = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quotes == 0)
			single = !single;
		if (str[i] == '\"' && single == 0)
			double_quotes = !double_quotes;
		i++;
	}
	if (single == 1 || double_quotes == 1)
		str = make_unclosed_quotes(str, double_quotes, single);
	return (str);
}
