/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:10:18 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/05 13:59:12 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_splitfree(char **ret, size_t i)
{
	while (i > 0)
	{
		free(ret[i - 1]);
		i--;
	}
	free(ret);
	return (NULL);
}

int		arg_count(char *str)
{
	size_t	i;
	int		ret;

	i = -1;
	ret = 0;
	while(str[++i])
	{
		if (!is_quoted(str, i))
		{
			if ((is_spc(str[i]) || is_op(str[i])) && i && !is_spc(str[i - 1]) && !is_op(str[i - 1]))
				ret++;
			if (is_op(str[i]))
			{
				ret++;
				if (str[i] != '|' && str[i + 1] == str[i])
					i++;
			}
		}
	}
	if (i && !is_spc(str[i - 1]))
		ret++;
	return (ret);
}

size_t	arg_len(char *str)
{
	size_t	ret;
	int		x;

	ret = 0;
	x = is_op(str[0]);
	if (!str || !str[0])
		return (0);
	if (x)
	{
		if (str[0] == str[1] && str[0] != '|')
			return (2);
		return (1);
	}
	while (str[ret] && ((!is_spc(str[ret]) && !is_op(str[ret])) || is_quoted(str, ret)))
		ret++;
	return (ret);
}

void	arg_cpy(char *dst, char *src, size_t *index)
{
	int		x;
	size_t	i;
	size_t	j;

	i = *index;
	j = 0;
	x = is_op(src[i]);
	if (x)
	{
		dst[j++] = src[i];
		if (src[i] != '|' && src[i] == src[i + 1])
			dst[j++] = src[i + 1];
	}
	else
	{
		while (src[i] && ((!is_spc(src[i]) && !is_op(src[i])) || is_quoted(src, i)))
			dst[j++] = src[i++];
	}
	dst[j] = '\0';
	*index = *index + j;
}

char	**ft_split_args(char *str)
{
	int		i;
	int		count;
	size_t	index;
	char	**ret;

	if (!str)
		return (NULL);
	i = -1;
	count = arg_count(str);
	index = 0;
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	while (++i < count)
	{
		while (str[index] && is_spc(str[index]))
			index++;
		ret[i] = (char *)malloc(sizeof(char) * (arg_len(&str[index]) + 1));
		if (!ret[i])
			return (ft_splitfree(ret, i));
		arg_cpy(ret[i], str, &index);
		while (str[index] && is_spc(str[index]))
			index++;
	}
	ret[count] = NULL;
	return (ret);
}

