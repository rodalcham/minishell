/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:30:05 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/10 13:41:47 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*lex(char **args)
{
	int		i;
	int		j;
	t_lexer	*head;
	t_lexer	*temp;

	i = 0;
	head = init_lexer(count_lex(args));
	temp = head;
	while (args[i])
	{
		handle_ops_open(temp, args, &i);
		j = 0;
		// while (args[i] && !is_op(args[i][0]))
		// 	temp->cmd[j++] = args[i++];
		// temp->cmd[j] = NULL;
		// handle_ops_close(temp, args, &i);
		i++;
	}
	return (head);
}

t_lexer	*init_lexer(int num)
{
	t_lexer	*head;
	t_lexer *temp;
	t_lexer	*prev;
	int	i;

	i = 0;
	head = NULL;
	while (i < num)
	{
		temp = (t_lexer *)malloc(sizeof(t_lexer));
		if (!temp)
			printf("\nFREE AND RETURN\n");
		if (!head)
			head = temp;
		else
			prev->next = temp;
		temp->cmd = NULL;
		temp->path = NULL;
		temp->input = NULL;
		temp->output = NULL;
		temp->next = NULL;
		prev=temp;
		i++;
	}
	return (head);
}

void	handle_ops_open(t_lexer *lex, char **args, int *i)
{
	if (!is_op(args[*i][0]))
		return ;
	if (args[*i][0] == '<')
	{
		if (args[*i][1] == '<')
			here_doc(lex, args, i);
		else
			add_input(lex, args, i);
	}
	else if (args[*i][0] == '>')
		add_output(lex, args, i);
	else if (args[*i][0] == '|')
	{
		//startpipe
		//add write pipe
		//go to next and add read pipe
	}
	(*i)++;
}

int	count_lex(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i][0] == '<' || args[i][0] == '>')
		{
			if (args[i + 1])
				i += 2;
			else
				i++;
		}
		else if (args[i][0] == '|')
			i++;
		else
		{
			count++;
			while (args[i] && !is_op(args[i][0]))
				i++;
		}
	}
	return (count);
}
