/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:20:41 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/08 17:44:51 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_pathjoin(char *path, char *cmd)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char *)malloc_t(sizeof(char)
			* (ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!ret)
		return (NULL);
	if (path)
		while (path[j])
			ret[i++] = path[j++];
	j = 0;
	ret[i++] = '/';
	while (cmd[j])
		ret[i++] = cmd[j++];
	ret[i] = '\0';
	return (ret);
}

char	*handle_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (free_t(path), NULL);
	if (!S_ISREG(statbuf.st_mode))
	{
		if (S_ISDIR(statbuf.st_mode))
			ft_perror(path, " is a directory\n", NULL);
		else if (S_ISLNK(statbuf.st_mode))
			ft_perror(path, " is a symbolic link\n", NULL);
		else
			ft_perror(path, " is not a file\n", NULL);
		*get_exit_status() = 126;
		free_t(path);
		path = ft_strdup("not_valid");
	}
	return (path);
}

char	*handle_absolute_path(char *command)
{
	char	*path;
	char	pwd[4096];
	int		i;

	if (command[0] == '.' || command[0] == '/')
	{
		path = ft_strdup(command);
		if (!path)
			return (NULL);
		i = ft_strlen(command);
		while (--i)
			if (path[i] == '/')
				break ;
		if (access(path, X_OK) == 0)
			return (handle_dir(path));
	}
	else
	{
		getcwd(pwd, 4096);
		path = ft_pathjoin(pwd, command);
		if (!path || access(path, X_OK) == 0)
			return (path);
	}
	return (free_t(path), ft_strdup("not_found"));
}

void	path_free(char **paths, int i)
{
	int j;

	j = i;
	while (paths[j])
	{
		free_t(paths[j]);
		j++;
	}
	free_t(paths);
}

char	*path_finder(char *command, char *envp)
{
	int		i;
	char	**paths;
	char	*ret;

	if (!command)
		return (ft_strdup("not_found"));
	if (command[0] == '.' || command[0] == '/' || !envp)
		return (handle_absolute_path(command));
	paths = ft_split(envp, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		ret = ft_pathjoin(paths[i], command);
		if (!ret)
			return (path_free(paths, i), NULL);
		if (access(ret, X_OK) == 0)
			return (path_free(paths, i), ret);
		free_t(paths[i]);
		free_t(ret);
	}
	return (free_t(paths), ft_strdup("not_found"));
}

char	*env_get_by_name(char *name)
{
	int		i;
	char	**env;
	size_t	name_len;

	env = *ft_env();
	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, name_len)
			&& env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}
