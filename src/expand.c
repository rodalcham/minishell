/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:47:16 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/05 16:23:25 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	str_int(char *dst, size_t *j);
char	*extract_env(char *str, char *buff);
void	str_app(char *dst, char *buff, size_t *j);
size_t	expand_len(char *str, char *buff, int mode);

void	do_expand(char *str, char *buff, char *ret, int mode)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && !is_spc(str[i + 1])
			&& (is_quoted(str, i) != 1 || mode) && str[i + 1] == '?' && ++i)
			str_int(&ret[j], &j);
		else if (str[i] == '$' && str[i + 1] && !is_spc(str[i + 1])
			&& (is_quoted(str, i) != 1 || mode))
		{
			str_app(&ret[j], env_get_by_name(extract_env(&str[i], buff)), &j);
			while (str[i + 1] && !is_spc(str[i + 1])
				&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
				i++;
		}
		else
			ret[j++] = str[i];
	}
	ret[j] = '\0';
}

char	*expand_tokens(char	*str, int mode)
{
	char	*buff;
	char	*ret;

	if (!str)
		return (NULL);
	buff = (char *)malloc_t(sizeof(char) * (ft_strlen(str) + 1));
	if (!buff)
		return (free_t(str), NULL);
	ret = (char *)malloc_t(sizeof(char) * (expand_len(str, buff, mode) + 1));
	if (!ret)
		return (free_t(str), free_t(buff), NULL);
	do_expand(str, buff, ret, mode);
	free_t(str);
	free_t(buff);
	return (ret);
}
