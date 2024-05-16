/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/15 12:25:16 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size == 0)
	{
		free (ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr)
	{
		if (ptr)
		{
			ft_memcpy(new_ptr, ptr, size);
			free (ptr);
		}
		else
			printf("Unable to allocate memory in ft_realloc");
	}
	return (new_ptr);
}
