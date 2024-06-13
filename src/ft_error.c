/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:09:53 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/13 14:49:50 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(int errno)
{
	if (errno == -1)
		printf("\nCANNOT ALLOCATE MEMORY.\n");
	else if (errno == -2)
		printf("\nFORK: MEMORY EXHAUSTED.\n");
	else if (errno == -3)
		printf("\nDUP2: CANNOT REDIRECT INPUT/OUTPUT.\n");
	else if (errno == -4)
		printf("\nEXECVE: FAILED TO REPLACE PROCESS.\n");
	ft_free_envp(get_envp());
	exit(0);
}
