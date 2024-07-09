/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:46:49 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/09 15:01:03 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*handle_unclosed_quotes(char *str)
{
	char	*ret;
	char	*new;

	if (!str)
		return (NULL);
	ret = str;
	while (is_quoted(str, ft_strlen(str)))
	{
		new = take_in("> ");
		if (!new)
			//do stuff
		ret = ft_strjoin(ret, new);
		free_t(str);
		if (!ret)
			return (NULL);
		str = ret;
	}
	return (ret);
}
