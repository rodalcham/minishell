/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:55 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/04 15:30:28 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_file	*new_file(void)
{
	t_file	*ret;

	ret = (t_file *)malloc(sizeof(t_file));
	if (!ret)
		return (NULL);
	return (ret);
}