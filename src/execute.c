/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:44:18 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/19 16:39:49 by rchavez@stu      ###   ########.fr       */
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
		if (temp->cmd)
			status = exec_do(temp);
		if (temp->input)
			close(temp->input->fd);
		if (temp->output)
			close(temp->output->fd);
		if (status)
			return (status);
		temp = temp->next;
	}
	temp = tokens;
	while (temp)
	{
		if (temp->pid != 0)
			waitpid(temp->pid, get_exit_status(), 0);
		temp = temp->next;
	}
	return (0);
}

int	replace_io(t_lexer *temp)
{
	if (temp->input)
	{
		if (dup2(temp->input->fd, STDIN_FILENO) < 0)
			return (-3);
		close(temp->input->fd);
	}
	if (temp->output)
	{
		if (dup2(temp->output->fd, STDOUT_FILENO) < 0)
			return (-3);
		close(temp->output->fd);
		if (!ft_strcmp(temp->output->filename, "PIPE")
			&& !ft_strcmp(temp->next->input->filename, "PIPE"))
			close(temp->next->input->fd);
	}
	return (0);
}

int	say_not_found(t_lexer *temp)
{
	if (access(temp->cmd[0], F_OK) == 0)
		printf("%s : Permission denied\n", temp->cmd[0]);
	else if (temp->cmd[0][0] == '/' || temp->cmd[0][0] == '.')
		printf("%s : no such file or directory\n", temp->cmd[0]);
	else
		printf("%s : command not found\n", temp->cmd[0]);
	*get_exit_status() = 127;
	return (0);
}

int	exec_do(t_lexer *temp)
{
	if ((!temp->cmd[0][0]) || (!ft_strncmp(temp->path, "not_found", 9)
		&& !ft_check_commands(temp)))
		return (say_not_found(temp));
	if ((temp->input && temp->input->fd < 0)
		|| (temp->output && temp->output->fd < 0)
		|| (!ft_strncmp(temp->path, "not_valid", 9)))
		return (0);
	temp->pid = fork();
	if (temp->pid == 0)
	{
		if (replace_io(temp) < 0)
			return (-3);
		if (ft_check_commands(temp))
			return (call_functions(temp));
		else if (execve(temp->path, temp->cmd, *ft_env()) < 0)
			return (-4);
	}
	else if (temp->pid < 0)
		return (-2);
	return (0);
}
