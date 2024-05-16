/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:55 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/16 16:01:42 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	handle_ctrlc(int signal)
{
	(void)signal;
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_ctrl_backslash(int signal)
{
	(void)signal;
}

void	signal_handler(void)
{
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, handle_ctrl_backslash);
}
