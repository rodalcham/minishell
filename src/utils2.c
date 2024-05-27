/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:51:05 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/27 15:05:58 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

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
