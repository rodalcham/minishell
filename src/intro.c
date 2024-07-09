/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:48:42 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/09 14:50:29 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	intro(void)
{
	char	*name;

	name = env_get_by_name("USER");
	if (!isatty(fileno(stdin)))
		return ;
	printf("\033[H\033[J");
	printf("        _   _   _   _   _   _   _   _   _   \n");
	printf("       / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ \n");
	printf("      ( M | I | N | I | S | H | E | L | L )\n");
	printf("       \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \n");
	printf("         ********************************\n");
	printf("\n    Welcome to Minishell by \033]8;;https://github.com/rodalcham"
		"\archavez\033]8;;\a && \033]8;;https://github.com/lglauch"
		"\alglauch\033]8;;\a\n\n");
	printf("         ********************************\n");
	if (name && name[0])
		printf("\n\t\tWelcome, %s\n", name);
}
