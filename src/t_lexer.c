/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:30:05 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/11 12:25:52 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*lex(char **args)
{
	int		i;
	t_lexer	*head;
	t_lexer	*temp;

	i = 0;
	head = init_lexer(count_lex(args));
	temp = head;
	while (args[i])
	{
		if (is_op(args[i][0]))
		{
			handle_ops_open(temp, args, &i);
			if (args[i] && args[i][0] == '|')
				temp = temp->next;
		}
		else
			temp->cmd = add_cmd(temp->cmd, args[i]);
		if (args[i])
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
		add_pipe(lex);
}

int	count_lex(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (args[i])
	{
		if (args[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

char	**add_cmd(char **cmd, char *str)
{
	int		i;
	int		size;
	char	**ret;

	i = -1;
	size = 0;
	while (cmd && cmd[size])
		size++;
	if (str)
		size++;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		printf("\nFREE AND RETURN\n");
	while (cmd && cmd[++i])
		ret[i] = cmd[i];
	if (!cmd)
		i++;
	ret[i++] = str;
	ret[i] = NULL;
	free(cmd);
	return (ret);
}
