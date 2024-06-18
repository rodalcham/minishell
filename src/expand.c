/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:08:57 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/18 16:11:30 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_inject_value(char *str, char *placeholder, char *envp_value)
{
	char	*rtr;
	char	*pos;
	int		str_len;
	int		placeholder_len;
	int		envp_value_len;

	str_len = ft_strlen(str);
	placeholder_len = ft_strlen(placeholder);
	envp_value_len = ft_strlen(envp_value);
	pos = ft_strnstr(str, placeholder, ft_strlen(str));
	if (pos == NULL)
		return (ft_strdup(str));
	rtr = malloc(sizeof(char) * (str_len - placeholder_len
				+ envp_value_len + 1));
	if (rtr == NULL)
		return (NULL);
	ft_strncpy(rtr, str, pos - str);
	rtr[pos - str] = '\0';
	ft_strlcat(rtr, envp_value, (pos) - (str) + envp_value_len + 1);
	ft_strlcat(rtr, pos + placeholder_len,
		str_len - placeholder_len + envp_value_len + 1);
	rtr[str_len - placeholder_len + envp_value_len] = 0;
	return (rtr);
}

char	*transform_variable(char *str, char *envp_name, char *envp_value)
{
	char	*placeholder;
	char	*new;

	placeholder = ft_strjoin("$", envp_name);
	if (envp_value == NULL)
		new = ft_inject_value(str, placeholder, "");
	else
		new = ft_inject_value(str, placeholder, envp_value);
	free (placeholder);
	return (new);
}

int	is_within_single_quotes(char *str, int index)
	{
	int	i;
	int	in_single_quotes;
	int	double_quotes;

	i = 0;
	double_quotes = 0;
	in_single_quotes = 0;
	while (i < index)
	{
		if (str[i] == '\"' && in_single_quotes == 0)
			double_quotes = !double_quotes;
		if (str[i] == '\'' && double_quotes == 0)
			in_single_quotes = !in_single_quotes;
		if (str[i] == '$' && !in_single_quotes)
			return (1);
		i++;
	}
	return (0);
}

char	*extract_env_name(char *str, int *i)
{
	int		j;
	char	*envp_name;

	if (str[*i] == '?')
	{
		envp_name = ft_strdup("?");
		(*i)++;
	}
	else
	{
		j = 0;
		envp_name = malloc(sizeof(char) * ft_strlen(&str[*i]) + 1);
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			envp_name[j++] = str[(*i)++];
		envp_name[j] = '\0';
	}
	return (envp_name);
}

char	*expand_tokens(char *str)
{
	int		i;
	char	*envp_name;
	char	*envp_value;
	char	*new;

	i = 0;
	if (!str || !str[0])
		return (0);
	new = ft_strdup(str);
	while (str[i])
	{
		if ((str[i] != '$' || !is_within_single_quotes(str, i + 1)) && ++i)
			continue ;
		i++;
		envp_name = extract_env_name(str, &i);
		if (ft_strcmp(envp_name, "?") == 0)
			envp_value = ft_itoa(*get_exit_status());
		else
			envp_value = env_get_by_name(envp_name);
		new = transform_variable(new, envp_name, envp_value);
		free(envp_name);
	}
	return (new);
}
