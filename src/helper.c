/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:05:50 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/24 12:32:09 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	make_expand(int quotes)
{
	int	rtr;

	rtr = 0;
	if (!quotes)
	{
		rtr = 1;
	}
	return (rtr);
}

size_t	ft_countwords(char const *s, char c)
{
	size_t	x;
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
