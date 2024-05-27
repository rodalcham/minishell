/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:09:53 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/05/24 09:56:26 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(int	errno)
{
	if (errno == -1)
		printf("\nMemory allocation failed.\n");
	exit(0);
}
