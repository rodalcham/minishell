/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:44:18 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/03 14:08:33 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute(t_lexer *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		prepare(tokens, i);
		if (tokens[i].path)
		{
			//fork and execve
		}
		resolve(tokens, i);
		i++;
	}
}

void	prepare(t_lexer *tokens, int i)
{
	int	fd;
	int pipes[2];

	if (!tokens[i].ops || !tokens[i].ops[0] || !tokens[i].ops[0][0])
		return ;
	if (tokens[i].ops[0][0] == '<' && tokens[i].ops[0][1] == '<')
	{
		//heredoc
	}
	else if (tokens[i].ops[0][0] == '>')
	{
		if (tokens[i].ops[0][1] == '>')	
			fd = open(tokens[i + 1].cmd[0], O_CREAT | O_APPEND | O_WRONLY);
		else
			fd = open(tokens[i + 1].cmd[0], O_CREAT | O_WRONLY | O_TRUNC);
		if (fd < 0)
			//free and return
		dup2(fd, STDOUT_FILENO);
	}
	else if (tokens[i].ops[0][0] == '<')
	{
		fd = open(tokens[i + 1].cmd[0], O_RDONLY);
		if (fd < 0)
			//free and return
		dup2(fd, STDIN_FILENO);
	}
	else if (tokens[i].ops[0][0] == '|')
	{
		if (pipe(pipes) < 0)
			//free and return
		

	}
}

void	resolve(t_lexer *tokens, int i)
{
	if (!tokens[i].ops || !tokens[i].ops[0] || !tokens[i].ops[0][0])
		return ;
	if (tokens[i].ops[0][0] == '<' && tokens[i].ops[0][1] == '<')
	{
		//heredoc
	}
	else if (tokens[i].ops[0][0] == '>' && tokens[i].ops[0][1] == '>')
	{

	}
	else if (tokens[i].ops[0][0] == '<')
	{

	}
	else if (tokens[i].ops[0][0] == '>')
	{

	}
	else if (tokens[i].ops[0][0] == '|')
	{

	}
}


pipe
fork
	dup2(output)
	execve(ls)
close(fd)
pipe
fork()
	dup2(input)
	dup2(output)
	execve(grep)
close(fd)
fork
	dup2(input)
	execve(awk)