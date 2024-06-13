/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:51:05 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/13 12:09:02 by rchavez          ###   ########.fr       */
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

char	*ft_strncpy(char *dest, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}

// void	*ft_realloc(void *ptr, size_t size)
// {
// 	void	*new_ptr;

// 	if (size == 0)
// 	{
// 		free (ptr);
// 		return (NULL);
// 	}
// 	new_ptr = malloc(size);
// 	if (new_ptr)
// 	{
// 		if (ptr)
// 		{
// 			ft_memcpy(new_ptr, ptr, size);
// 			free (ptr);
// 		}
// 		else
// 			printf("Unable to allocate memory in ft_realloc");
// 	}
// 	return (new_ptr);
// }
