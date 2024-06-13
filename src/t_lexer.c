/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:30:05 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/13 15:03:39 by rchavez          ###   ########.fr       */
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
			temp->cmd = add_cmd(temp, args[i]);
		if (args[i])
			i++;
	}
	return (head);
}

t_lexer	*init_lexer(int num)
{
	t_lexer	*head;
	t_lexer	*temp;
	t_lexer	*prev;
	int		i;

	i = -1;
	head = NULL;
	while (++i < num)
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
		temp->pid = 0;
		prev = temp;
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

char	**add_cmd(t_lexer *lex, char *str)
{
	int		i;
	int		size;
	char	**ret;

	i = -1;
	size = 0;
	while (lex->cmd && lex->cmd[size])
		size++;
	ret = (char **)malloc(sizeof(char *) * (size + 2));
	if (!ret)
		printf("\nFREE AND RETURN\n");
	while (lex->cmd && lex->cmd[++i])
		ret[i] = lex->cmd[i];
	if (!lex->cmd)
		i++;
	ret[i++] = str;
	ret[i] = NULL;
	if (!lex->cmd)
	{
		lex->path = path_finder(ret[0], env_get_by_name("PATH"));
		if (!lex->path)
			printf("\nFREE AND RETURN\n");
	}
	free(lex->cmd);
	return (ret);
}
