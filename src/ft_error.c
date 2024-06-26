/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:09:53 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/26 12:12:05 by rchavez          ###   ########.fr       */
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
	else if (errno == -5)
		printf("\nPIPE: MEMORY EXHAUSTED.\n");
	// ft_free_envp(*get_envp());
	exit(*get_exit_status());
}
