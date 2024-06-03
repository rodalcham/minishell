/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:08:57 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/03 17:16:14 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_tokens(char *str, char *original, int count)
{
	int		i;
	int		j;
	int		x;
	char	*envp_name;
	char	*envp_value;
	char	*new;

	i = 0;
	j = 0;
	x = 0;
	while (str[i] && str[i] != ' ' && str[i] != '"')
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			envp_value = env_get_by_name("$$");
			break ;
		}
		envp_name[j++] = str[i++];
	}
	envp_value = env_get_by_name(envp_name);
	
}