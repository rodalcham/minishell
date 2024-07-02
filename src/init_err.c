/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:44:14 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/02 14:53:35 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_perror(char *s1, char *s2, char *s3)
{
	if (s1)
		perror(s1);
	if (s2)
		perror(s2);
	if (s3)
		perror(s3);
}
