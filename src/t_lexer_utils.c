/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:00:15 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/09 15:04:51 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_lexer(t_lexer *temp)
{
	temp->cmd = NULL;
	temp->path = NULL;
	temp->input = NULL;
	temp->output = NULL;
	temp->next = NULL;
	temp->pid = 0;
}
