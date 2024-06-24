/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:28 by leo               #+#    #+#             */
/*   Updated: 2024/06/24 09:23:37 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_len(char **env)
{
	int i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i + 1);
}

int	env_cmp(char *s1, char *s2)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!s1 || !s2)
		return (0);
	while(s1[i] && s2[i] && s1[i] != '=' && s2[i] != '='
		&& s1[i] != '+' && s2[i] != '+')
	{
		if (s1[i] != s2[i])
			ret = s1[i] - s2[i];
		i++;
	}
	if (!ret)
		ret = s1[i] - s2[i];
	if (s1[i] == '=' || s1[i] == '+')
		ret -= s1[i];
	if (s2[i] == '=' || s2[i] == '+')
		ret += s2[i];
	return (ret);
}

int env_pos(char **env, char *cmd)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i])
	{
		if (!env_cmp(env[i], cmd))
			return (i);
		i++;
	}
	return (-1);
}

int	envp_add(char **env, char *cmd, int pos, char *eq)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (env_len(env) + 1));
	if (!new)
		return (-1);
	if (eq && eq != cmd && *(eq - 1) == '+')
	{
		eq--;
		while (*(++eq))
			*(eq - 1) = *(eq);
		*(eq - 1) = '\0';
	}
	i = -1;
	while (env[++i])
		new[i] = env[i];
	new[i] = ft_strdup(cmd);
	if (!new[i])
		return (free(new), -1);
	new[++i] = NULL;
	*ft_env() = new;
	if (pos >= 0)
		free(env);
	return (0);
}

int	envp_update_value(char **env, char *cmd, int pos, char *eq)
{
	char *new;

	new = NULL;
	if (eq && eq != cmd && *(eq - 1) == '+' && *(eq + 1))
		new = ft_strjoin(env[pos], (eq + 1));
	else if (eq)
		new = ft_strdup(cmd);
	else
		return (0);
	if (!new)
		return (-1);
	free(env[pos]);
	env[pos] = new;
	return (0);
}

// int	export_command(t_lexer *lexer)
// {
// 	char	*cmd;
// 	char	*eq;
// 	int		pos;

// 	if (!lexer->cmd[1])
// 	{
// 		printf("export : INVALID USAGE\n");
// 		return (*get_exit_status() = 0);
// 	}
// 	cmd = *last_line();
// 	eq = ft_strchr(cmd, '=');
// 	if ((eq && eq != cmd && *(eq - 1) == '-')
// 		|| (!eq && (ft_strchr(cmd, '+') || ft_strchr(cmd, '-'))))
// 	{
// 		printf("export : '%s' : not a valid identifier\n", cmd);
// 		return (*get_exit_status() = 1);
// 	}
// 	if (!eq || lexer->next)
// 		return (*get_exit_status() = 0);
// 	pos = env_pos(*ft_env(), cmd);
// 	if (pos >= 0)
// 		return (envp_update_value(*ft_env(), cmd, pos, eq));
// 	else
// 		return (envp_add(*ft_env(), cmd, pos, eq));
// }

int	env_split(char **name, char **value, char *line)
{
	int		i;
	char	*eq;

	i = 0;
	while (*line && is_spc(*line))
		line++;
	line += ft_strlen("export");
	eq = ft_strchr(line, '=');
	if (!eq)
		return(1);
	if (eq == line || *(eq - 1) == '-' || is_spc(*(eq - 1)))
	{
		printf("export : '%s' : not a valid identifier\n", eq);
		return (1);
	}
	*eq = '\0';
	eq++;
	*name = ft_strdup(line);
	if (!*name)
		return (-1);
	*value = ft_strdup(eq);
	if (!*value)
		return (free(*name), -1);
	return (0);
}

int	env_join(char **name, char **value);

int	export_command(t_lexer *lexer)
{
	char	*name;
	char	*value;
	int		pos;
	int		stat;

	stat = env_split(&name, &value, *last_line());
	if (lexer->next || stat == 1)
		return (*get_exit_status() = 0);
	if (stat < 0 || env_join(&name, &value))
		return (-1);
	pos = env_pos(*ft_env(), name);
	if (pos >= 0)
		return (envp_update_value(*ft_env(), name, value, pos));
	else
		return (envp_add(*ft_env(), name, value, pos));
}
