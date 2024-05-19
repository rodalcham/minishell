/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:07:51 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/05/19 13:30:28 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	***tokenize(char **args)
{
	char	***ret;
	int		i;
	int		j;
	int		a;

	i = 0;
	a = 0;
	if (sep(args[i][0]) > 2)
		return (printf("parse error near '%c'", args[i][0]));
	ret = (char ***)malloc(sizeof(char **) * (c_tokens(args) + 1));
	if (!ret)
		printf("Memory error"); //FREE!!!!!
	while (args[i])
	{
		j = 0;
		if (sep(args[i][0]) < 3)
		{
			ret[a] = (char **)malloc(sizeof(char *) * (c_args(&args[i]) + 1));
			if (!ret[a])
				printf("Memory error"); //FREE!!!!!
			while (args[i] && sep(args[i][0]) < 3)
				ret[a][j++] = args[i++];
			ret[a][j] = NULL;
			a++;
		}
		else
		{
			ret[a] = (char **)malloc(sizeof(char *) * (c_ops(&args[i]) + 1));
			if (!ret[a])
				printf("Memory error"); //FREE!!!!!
			while (args[i] && sep(args[i][0]) > 2)
				ret[a][j++] = args[i++];
			ret[a][j] = NULL;
			a++;
		}
	}
	ret[a] = NULL;
	return (ret);
}

int	c_args(char	**args)
{
	int	i;

	i = 0;
	if (!args || !args[0])
		return (0);
	while (args[i] && sep(args[i][0]) < 3)
		i++;
	return (i);
}

int	c_ops(char	**args)
{
	int	i;

	i = 0;
	if (!args || !args[0])
		return (0);
	while (args[i] && sep(args[i][0]) > 2)
		i++;
	return (i);
}

int	c_tokens(char **args)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!args || !args[0])
		return (0);
	while (args[i])
	{
		if (sep(args[i]) < 3)
		{
			ret++;
			while (args[i] && sep(args[i][0]) < 3)
				i++;
		}
		else
		{
			ret++;
			while (args[i] && sep(args[i][0]) > 2)
				i++;
		}
	}
	return (ret);
}
