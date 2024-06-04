/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:30:05 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/04 15:46:13 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*lex(char **args)
{
	int	i;
	int	j;
	t_lexer	*head;
	t_lexer *temp;

	i = 0;
	if ()
	head = new_lexer();
	temp = head;
	while (args[i])
	{
		j = 0;
		while (args[i] && !is_op(args[i][0]))
			temp->cmd[j++] = args[i++];
		temp->cmd[j] = NULL;
		
		i++;
	}
}

t_lexer	*new_lexer()
{
	t_lexer	*ret;

	ret = (t_lexer *)malloc(sizeof(t_lexer));
	if (!ret)
		return (NULL);
	ret->cmd = NULL;
	ret->path = NULL;
	ret->input = NULL;
	ret->output = NULL;
	return (ret);
}
