/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:30:05 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/09 14:01:36 by rchavez@stu      ###   ########.fr       */
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
	head = new_lexer();
	if (!head)
		printf("\nFREE AND RETURN\n");
	temp = head;
	while (args[i])
	{
		handle_ops_open(temp, args, &i);
		j = 0;
		while (args[i] && !is_op(args[i][0]))
			temp->cmd[j++] = args[i++];
		temp->cmd[j] = NULL;
		handle_ops_close(temp, args, &i);
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
	ret->next = NULL;
	return (ret);
}

void	handle_ops_open(t_lexer *lex, char **args, int *i)
{
	if (!is_op(args[*i][0]))
		return ;
	if (args[*i][0] == '<')
	{
		if(args[*i][1] == '<')
			here_doc(lex, args, i);
		else
			add_input(lex, args, i);
	}
	else if (args[*i][0] == '>')
		add_output(lex, args, i);
	else if ()
}

