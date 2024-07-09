/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/09 16:00:15 by rchavez          ###   ########.fr       */
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

int	sep(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	if (c == '<')
		return (3);
	if (c == '>')
		return (4);
	if (c == '|')
		return (5);
	return (0);
}

// char	*make_unclosed_quotes(char *str, int double_quotes, int single)
// {
// 	char	*new_input;
// 	char	*new_str;
// 	int		i;

// 	new_str = malloc_t(sizeof(char) * ft_strlen(str) + 2);
// 	ft_strcpy(new_str, str);
// 	ft_strlcat(new_str, "\n", ft_strlen(new_str) + 2);
// 	while (double_quotes == 1 || single == 1)
// 	{
// 		new_input = take_in("> ");
// 		if (!new_input)
// 			return (NULL);
// 		new_str = realloc(new_str, sizeof(char) * (ft_strlen(new_str)
// 					+ ft_strlen(new_input) + 3));
// 		if (!new_str)
// 		{
// 			free_t(new_input);
// 			return (NULL);
// 		}
// 		ft_strlcat(new_str, new_input, ft_strlen(new_str)
// 			+ ft_strlen(new_input) + 2);
// 		ft_strlcat(new_str, "\n", ft_strlen(new_str) + 2);
// 		i = 0;
// 		while (new_input[i])
// 		{
// 			if (new_input[i] == '"' && double_quotes == 1)
// 			{
// 				double_quotes = 0;
// 			}
// 			else if (new_input[i] == '\'' && single == 1)
// 			{
// 				single = 0;
// 			}
// 			i++;
// 		}
// 		free_t(new_input);
// 	}
// 	return (new_str);
// }

char	*ft_strnljoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = -1;
	j = -1;
	p = (char *) malloc_t_bad((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!p)
		return (NULL);
	while (s1[++i])
		p[i] = s1[i];
	p[i++] = '\n';
	while (s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	return (p);
}

char	*handle_unclosed_quotes(char *str)
{
	char	*ret;
	char	*new;

	if (!str)
		return (NULL);
	if (!is_quoted(str, ft_strlen(str) - 1))
		return (str);
	ret = str;
	while (is_quoted(ret, ft_strlen(ret) - 1))
	{
		new = take_in("> ");
		if (!new)
			return (NULL);
		ret = ft_strnljoin(ret, new);
		if (str)
			free_t(str);
		if (!ret)
			return (NULL);
		str = ret;
	}
	return (ret);
}
