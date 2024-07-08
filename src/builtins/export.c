/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:28 by leo               #+#    #+#             */
/*   Updated: 2024/07/08 23:39:07 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	declare_usage(void);

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

char	*get_es(char *ev)
{
	size_t	i;

	i = 0;
	while (ev[i])
	{
		if (is_spc(ev[i]))
			return (&ev[i]);
		i++;
	}
	return (NULL);
}

int	do_export(t_lexer *lexer, char *ev)
{
	char	*eq;
	int		pos;
	char	*es;

	eq = ft_strchr(ev, '=');
	es = get_es(ev);
	pos = env_pos(*ft_env(), ev);
	if ((eq && (eq == ev || (ft_strchr(ev, '-') && ft_strchr(ev, '-') < eq)
		|| is_spc(*(eq - 1)) || (ft_strchr(ev, '?')
		&& ft_strchr(ev, '?') < eq))) || !ev[0] || (es && eq && es < eq))
	{
		ft_perror("export : `", ev, "' : not a valid identifier\n");
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
