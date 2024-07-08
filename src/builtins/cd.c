/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:13:59 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/08 16:55:24 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_cwd(void)
{
	char	buff[4100];
	char	*ev;
	char	*eq;
	int		pos;

	ft_strcpy(buff, "PWD=");
	getcwd(&buff[4], 4096);
	ev = &buff[0];
	eq = &buff[3];
	pos = env_pos(*ft_env(), ev);
	if (pos >= 0)
		return (envp_update_value(*ft_env(), ev, pos, eq));
	else
		return (envp_add(*ft_env(), ev, pos, eq));
}

int	update_ocwd(void)
{
	char	buff[4103];
	char	*ev;
	char	*eq;
	int		pos;

	ft_strcpy(buff, "OLDPWD=");
	getcwd(&buff[7], 4096);
	ev = &buff[0];
	eq = &buff[6];
	pos = env_pos(*ft_env(), ev);
	if (pos >= 0)
		return (envp_update_value(*ft_env(), ev, pos, eq));
	else
		return (envp_add(*ft_env(), ev, pos, eq));
}

void	cd_expand_home(t_lexer *lexer, char path[], int *i)
{
	if (!lexer->cmd[1] || (lexer->cmd[1][0] == '~' && (!lexer->cmd[1][1] || lexer->cmd[1][1] == '/')))
	{
		if (env_pos(*ft_env(), "HOME") < 0)
		{
			write(2, "cd: HOME not set\n", 17);
			*get_exit_status() = 1;
			*i = -1;
		}
		else
		{
			if (!lexer->cmd[1] || (lexer->cmd[1][0] == '~' && (!lexer->cmd[1][1] || lexer->cmd[1][1] == '/')))
				ft_strlcpy(path, env_get_by_name("HOME"), 4096);
			if (lexer->cmd[1] && lexer->cmd[1][0] == '~')
				ft_strlcpy(&path[ft_strlen(path)], &lexer->cmd[1][1], 4096 - ft_strlen(path));
			*i = 1;
		}
	}
}

void	cd_expand_old(t_lexer *lexer, char path[], int *i)
{
	if (*i)
		return ;
	if (!ft_strcmp(lexer->cmd[1], "-"))
	{
		if (env_pos(*ft_env(), "OLDPWD") < 0)
		{
			write(2, "cd: OLDPWD not set\n", 19);
			*get_exit_status() = 1;
			*i = -1;
		}
		else
		{
			ft_strlcpy(path, env_get_by_name("OLDPWD"), 4096);
			*i = 2;
		}
	}
}

int	cd_command(t_lexer *lexer)
{
	char	path[4096];
	int		i;

	i = 0;
	cd_expand_home(lexer, path, &i);
	cd_expand_old(lexer, path, &i);
	if (update_ocwd() < 0)
		return (-1);
	if (!i && lexer->cmd[1])
		ft_strlcpy(path, lexer->cmd[1], 4096);
	if (i >= 0)
	{
		if (chdir(path) == -1)
		{
			ft_perror("cd: ", path, ": No such file or directory\n");
			*get_exit_status() = 1;
		}
		else
			*get_exit_status() = 0;
		if (*get_exit_status() == 0 && i ==2)
			printf("%s\n",path);
	}
	if (update_cwd() < 0)
		return (-1);
	return (*get_exit_status());
}
