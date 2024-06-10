/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:48:41 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/10 11:16:15 by lglauch          ###   ########.fr       */
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
