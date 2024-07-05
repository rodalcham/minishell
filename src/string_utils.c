/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:05:50 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/05 16:47:18 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_countwords(char const *s, char c)
{
	int		x;
	size_t	i;

	x = 0;
	i = 0;
	if (*s)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			x++;
		i++;
	}
	if (*s && s[i] == '\0' && s[i - 1] != c)
		x++;
	return (x);
}

int	is_forkable(t_lexer *temp)
{
	if (ft_strcmp("cd", temp->cmd[0]) && ft_strcmp("export", temp->cmd[0])
		&& ft_strcmp("unset", temp->cmd[0])
		&& ft_strcmp("exit", temp->cmd[0]))
		return (1);
	return (0);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		q;

	i = 0;
	j = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i];
			while (str[++i] && str[i] != q)
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		if (str[i])
			i++;
	}
	str[j] = '\0';
	return (str);
}

int	is_quoted(char *str, size_t index)
{
	size_t	i;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	i = 0;
	if (!str || index >= ft_strlen(str))
		return (0);
	while (str[i] && i <= index)
	{
		if (str[i] == '\'' && !dq)
			sq = !sq;
		else if (str[i] == '\"' && !sq)
			dq = !dq;
		i++;
	}
	if (sq)
		return (1);
	if (dq)
		return (2);
	return (0);
}

int	has_quotes(char	*str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (is_quoted(str, i))
			return (1);
		i++;
	}
	return (0);
}
