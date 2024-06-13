/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:44:18 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/13 15:04:44 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute(t_lexer *tokens)
{
	t_lexer	*temp;
	int		status;

	temp = tokens;
	while (temp)
	{
		status = exec_do(temp);
		if (status)
			return (status);
		if (temp->output)
			close(temp->output->fd);
		temp = temp->next;
	}
	temp = tokens;
	while (temp)
	{
		if (temp->pid)
			waitpid(temp->pid, get_exit_status(), 0);
		if (temp->input)
			close(temp->input->fd);
		temp = temp->next;
	}
	return (0);
}

int	exec_do(t_lexer *temp)
{
	if (!ft_strncmp(temp->path, "not_found", 9)) //&!isbuiltin
	{
		printf("%s : COMMAND NOT FOUND\n", temp->cmd[0]);
		return (0);
	}
	temp->pid = fork();
	if (temp->pid == 0)
	{
		if (temp->input)
			if (dup2(temp->input->fd, STDIN_FILENO) < 0)
				return (-3);
		if (temp->output)
			if (dup2(temp->output->fd, STDOUT_FILENO) < 0)
				return (-3);
		//if (is_builtin)
		//do_builtin \n else
		if (execve(temp->path, temp->cmd, NULL) < 0)
			return (-4);
	}
	else if (temp->pid < 0)
		return (-2);
	return (0);
}
