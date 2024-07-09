/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:49:13 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/09 16:49:50 by rchavez          ###   ########.fr       */
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
	char		buff[4103];
	char		*ev;
	char		*eq;
	int			pos;
	static int	i = 0;

	ft_strcpy(buff, "OLDPWD=");
	getcwd(&buff[7], 4096);
	ev = &buff[0];
	eq = &buff[6];
	pos = env_pos(*ft_env(), ev);
	if (pos >= 0)
		return (envp_update_value(*ft_env(), ev, pos, eq));
	else if (!i && ++i)
		return (envp_add(*ft_env(), ev, pos, eq));
	return (0);
}

void	cd_expand_home(t_lexer *lexer, char path[], int *i)
{
	if (!lexer->cmd[1] || (lexer->cmd[1][0] == '~' && (!lexer->cmd[1][1]
		|| lexer->cmd[1][1] == '/')))
	{
		if (env_pos(*ft_env(), "HOME") < 0)
		{
			write(2, "cd: HOME not set\n", 17);
			*get_exit_status() = 1;
			*i = -1;
		}
		else
		{
			if (!lexer->cmd[1] || (lexer->cmd[1][0] == '~'
				&& (!lexer->cmd[1][1] || lexer->cmd[1][1] == '/')))
				ft_strlcpy(path, env_get_by_name("HOME"), 4096);
			if (lexer->cmd[1] && lexer->cmd[1][0] == '~')
				ft_strlcpy(&path[ft_strlen(path)], &lexer->cmd[1][1],
					4096 - ft_strlen(path));
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
