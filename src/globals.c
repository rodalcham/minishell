/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:48:41 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/16 14:45:53 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*get_run(void)
{
	static int	run = 1;

	return (&run);
}

t_envp	**get_envp(void)
{
	static t_envp	*envp = NULL;

	return (&envp);
}

int	*get_exit_status(void)
{
	static int	status = 0;

	return (&status);
}

char	***ft_env(void)
{
	static char	**env = NULL;

	return (&env);
}
