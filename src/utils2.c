/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:51:05 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/13 12:40:30 by lglauch          ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	int			j;
	int			i;

	i = 0;
	j = ft_strlen((char *)s);
	while (i <= j)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((char)c == 0)
		return ((char *)&s[i]);
	return (NULL);
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
