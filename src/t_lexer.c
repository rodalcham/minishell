/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:30:05 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/09 15:01:29 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*lex(char **args, int *status)
{
	int		i;
	t_lexer	*head;
	t_lexer	*temp;

	i = -1;
	head = init_lexer(count_lex(args));
	if (!head)
		return (*status = -1, NULL);
	temp = head;
	while (args[++i] && *status >= 0)
	{
		if (is_op(args[i][0]))
		{
			*status = handle_ops_open(temp, args, &i);
			if (args[i] && args[i][0] == '|')
				temp = temp->next;
		}
		else
		{
			temp->cmd = add_cmd(temp, remove_quotes(args[i]));
			if (!temp->cmd)
				return (*status = -1, head);
		}
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
		temp = (t_lexer *)malloc_t(sizeof(t_lexer));
		if (!temp)
		{
			prev->next = NULL;
			return (free_lexer(head), NULL);
		}
		if (!head)
			head = temp;
		else
			prev->next = temp;
		set_lexer(temp);
		prev = temp;
	}
	*get_lexer() = head;
	return (head);
}

int	handle_ops_open(t_lexer *lex, char **args, int *i)
{
	int	status;

	status = 0;
	if (lex->cmd && (!is_forkable(lex)))
		return (0);
	if (args[*i][0] == '<')
	{
		if (args[*i][1] == '<')
			status = (add_heredoc(lex, args, i));
		else
			status = (add_input(lex, args, i));
	}
	else if (args[*i][0] == '>')
		status = (add_output(lex, args, i));
	else if (args[*i][0] == '|')
		status = (add_pipe(lex));
	if (status < 0 || (lex->input && lex ->input->fd < 0)
		|| (lex->output && lex->output->fd < 0))
		*get_exit_status() = 1;
	return (status);
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
	ret = (char **)malloc_t(sizeof(char *) * (size + 2));
	if (!ret)
		return (free_t(lex->cmd), NULL);
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
			return (free_t(ret), free_t(lex->cmd), NULL);
	}
	free_t(lex->cmd);
	return (ret);
}
