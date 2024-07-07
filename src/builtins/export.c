/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:28 by leo               #+#    #+#             */
/*   Updated: 2024/07/07 15:48:37 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_cmp(char *s1, char *s2)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '='
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

int	env_pos(char **env, char *cmd)
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

int	declare_usage(void)
{
	char	**env;
	int		i;

	env = *ft_env();
	i = -1;
	while (env && env[++i])
		printf("declare -x %s\n", env[i]);
	*get_exit_status() = 0;
	return (0);
}

int	do_export(t_lexer *lexer, char *ev)
{
	char	*eq;
	int		pos;

	eq = ft_strchr(ev, '=');
	pos = env_pos(*ft_env(), ev);
	if ((eq && (eq == ev || (ft_strchr(ev, '-') && ft_strchr(ev, '-') < eq)
			|| is_spc(*(eq - 1)))) || !ev[0])
	{
		ft_perror_spc("export : `", ev, "' : not a valid identifier\n");
		return (*get_exit_status() = 1);
	}
	if (lexer->next || !eq || *get_lexer() != lexer)
		return (*get_exit_status() = 0);
	if (pos >= 0)
		return (envp_update_value(*ft_env(), ev, pos, eq));
	else
		return (envp_add(*ft_env(), ev, pos, eq));
	return (0);
}

int	export_command(t_lexer *lexer)
{
	char	*ev;
	int		i;

	i = 0;
	if (!lexer->cmd[1])
		return (declare_usage());
	while (lexer->cmd[++i])
	{
		ev = lexer->cmd[i];
		if (do_export(lexer, ev) < 0)
			return (-1);
	}
	return (*get_exit_status());
}
