/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:05:50 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/26 11:33:30 by rchavez          ###   ########.fr       */
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

void shift_left(char *str)
{
	size_t	i;
	if (!str || !str[0])
		return ;
	i = 0;
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] ='\0';
}

char	*remove_uquotes(char *str)
{
	size_t	i;
	size_t	q;
	int	spc;

	i = 0;
	q = 0;
	spc = 0;
	while (str && str[i] && ++i)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (q && str[i - 1] == str[q])
			{
				shift_left(&str[i - 1]);
				shift_left(&str[q - 1]);
				q = 0;
				spc = 0;
			}
			else if (!q)
				q = i;
		}
		else if(q && is_spc(str[i - 1]))
			spc = 1;
	}
	return (str);
}
