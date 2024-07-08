/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:55 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/08 20:48:54 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_ctrlc(int signal)
{
	(void)signal;
	if (g_signal == 0)
	{
		write(1, "\n", 1);
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		*get_exit_status() = 1;
	}
}

void	signal_handler(void)
{
	if (g_signal == 0)
		signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_temp(int signal)
{
	(void)signal;
	*get_exit_status() = 130;
}
