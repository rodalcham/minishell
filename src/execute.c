/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:44:18 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/11 16:05:32 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_lexer *tokens)
{
	t_lexer	*temp;

	temp = tokens;
	while (temp)
	{
		exec_do(temp);
		// if (temp->input)
		// 	close(temp->input->fd);
		if (temp->output)
			close(temp->output->fd);
		temp = temp->next;
	}
	temp = tokens;
	while (temp)
	{
		waitpid(temp->pid, get_exit_status(), 0);
		temp = temp->next;
	}
}

void	exec_do(t_lexer *temp)
{
	int	t_pid;

	t_pid = fork();
	if (t_pid == 0)
	{
		if (temp->input)
			if (dup2(temp->input->fd, STDIN_FILENO) < 0)
				printf("\nFREE AND RETURN\n");
		if (temp->output)
			if (dup2(temp->output->fd, STDOUT_FILENO) < 0)
				printf("\nFREE AND ARETURN\n");
		//if (is_builtin)
		//do_builtin \n else
		if (temp->path && ft_strncmp(temp->path, "not_found", 9))
		{
			if (execve(temp->path, temp->cmd, NULL) < 0)
				printf("\nFREE AND RETURN\n");
		}
		else
			printf("\nFREE AND RETURN\n");
	}
	else if (t_pid < 0)
		printf("\nFREE AMD RETURN\n");
	else
		temp->pid = t_pid;
}
