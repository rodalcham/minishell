/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:36:51 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/09 14:35:03 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_env(char *str, char *buff)
{
	size_t	i;

	i = 1;
	while (str[i] && !is_spc(str[i]) && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		buff[i - 1] = str[i];
		i++;
	}
	buff[i - 1] = '\0';
	return (buff);
}

size_t	expand_len(char *str, char *buff, int mode)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !is_spc(str[i + 1])
			&& (is_quoted(str, i) != 1 || mode) && str[i + 1] == '?' && ++i)
			ret += 7;
		else if (str[i] == '$' && str[i + 1] && !is_spc(str[i + 1])
			&& (is_quoted(str, i) != 1 || mode) && !((is_spc(str[i + 1])
					|| sep(str[i + 1])) && is_quoted(str, i)))
		{
			ret += ft_strlen(env_get_by_name(extract_env(&str[i], buff)));
			while (str[i + 1] && !is_spc(str[i + 1])
				&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
				i++;
		}
		else
			ret++;
		i++;
	}
	return (ret);
}

void	str_app(char *dst, char *buff, size_t *j)
{
	size_t	i;

	i = 0;
	if (!buff)
		return ;
	while (buff[i])
	{
		dst[i] = buff[i];
		i++;
	}
	*j += ft_strlen(buff);
}

void	str_int(char *dst, size_t *j)
{
	int		i;
	int		len;

	i = *get_exit_status();
	len = 0;
	if (i == 0)
		len = 1;
	else
	{
		while (i)
		{
			len++;
			i = i / 10;
		}
	}
	i = *get_exit_status();
	*j += len;
	while (len)
	{
		dst[len - 1] = i % 10 + '0';
		i = i / 10;
		len--;
	}
}
