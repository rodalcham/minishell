/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:07:51 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/05/27 12:24:53 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_lex(char *line)
{
	int	i;
	int	last;
	int	count;

	i = 0;
	count = 0;
	last = 1;
	while (line[i])
	{
		if (is_op(line[i]))
		{
			last = 1;
			count++;
			while (line [i] && (is_op(line[i]) || is_spc(line[i])))
				i++;
			i--;
		}
		else if (!is_spc(line[i]))
			last = 0;
		i++;
	}
	if (!last)
		count++;
	return (count);
}

int	c_cmd(char **args, int *j)
{
	int	i;

	i = *j;
	while (args[*j] && !is_op(args[*j][0]))
		*j += 1;
	return (*j - i);
}

int	c_ops(char **args, int *j)
{
	int	i;

	i = *j;
	while (args[*j] && is_op(args[*j][0]))
		*j += 1;
	return (*j - i);
}

t_lexer	*tokenize(char *line, char **args)
{
	t_lexer	*ret;
	int		i;
	int		j;
	int		count;

	count = count_lex(line);
	i = -1;
	j = 0;
	ret = (t_lexer *)malloc(sizeof(t_lexer) * (count + 1)); // +1 if you want to null terminate
	if (!ret)
		free_fail(ret, args, line, i);
	while (++i < count)
	{
		ret[i].path = NULL;
		ret[i].cmd = (char **)malloc(sizeof(char *) * (c_cmd(args, &j) + 1));
		if (!ret[i].cmd)
			free_fail(ret, args, line, i);
		ret[i].ops = (char **)malloc(sizeof(char *) * (c_ops(args, &j) + 1));
		if (!ret[i].ops)
			free_fail(ret, args, line, i);
	}
	return (token_fill(ret, args, line));
}

t_lexer	*token_fill(t_lexer *ret, char **args, char *line)
{
	int			i;
	int			j;
	int			z;

	i = 0;
	z = 0;
	while (args[i])
	{
		j = 0;
		while (args[i] && !is_op(args[i][0]))
			ret[z].cmd[j++] = args[i++];
		ret[z].cmd[j] = NULL;
		j = 0;
		while (args[i] && is_op(args[i][0]))
			ret[z].ops[j++] = args[i++];
		ret[z].ops[j] = NULL;
		z++;
	}
	ret[z].cmd = NULL;
	return (fill_paths(ret, args, line));
}

t_lexer	*fill_paths(t_lexer *ret, char **args, char *line)
{
	int	i;
	int	z;

	i = 0;
	z = count_lex(line);
	while (i < z)
	{
		ret[i].path = path_finder(ret[i].cmd[0], getenv("PATH"));
		if (!ret[i].path)
			free_fail(ret, args, line, z - 1);
		else
			i++;
	}
	return(ret);
}
