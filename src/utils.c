/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/09 16:46:05 by rchavez          ###   ########.fr       */
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

char	*ft_strnljoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = -1;
	j = -1;
	p = (char *)malloc_t_bad((ft_strlen(s1)
				+ ft_strlen(s2) + 2) * sizeof(char));
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
