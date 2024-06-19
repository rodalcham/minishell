/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:20:41 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/19 14:20:05 by rchavez          ###   ########.fr       */
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
	ret = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmd) + 2));
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

char *handle_dir(char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) == -1)
		return (free(path), NULL);
	if (path[0] != '.')
		return (path);
	if (!S_ISREG(statbuf.st_mode))
	{
		if (S_ISDIR(statbuf.st_mode)) 
        	printf("%s is a directory\n", path);
		else if (S_ISLNK(statbuf.st_mode)) 
    	    printf("%s is a symbolic link\n", path);
		else 
        	printf("%s is not a file\n", path);
		*get_exit_status() = 126;
		free(path);
		path = ft_strdup("not_valid");
    }
	return (path);
}

char	*handle_absolute_path(char *command)
{
	char	*path;
	int		i;
	int		j;

	path = ft_strdup(command);
	if (!path)
		return (NULL);
	i = ft_strlen(command);
	j = 0;
	while (i)
	{
		if (path[i] == '/')
			break;
		i--;
	}
	if (i >= 0)
	{
		while (path[++i])
			command[j++] = path[i];
		command[j] = '\0'; 
	}
	if (access(path, X_OK) == 0)
		return (handle_dir(path));
	return(free(path), ft_strdup("not_found"));
}

char	*path_finder(char *command, char *envp)
{
	int		i;
	char	**paths;
	char	*ret;

	if (!command)
		return (ft_strdup("not_found"));
	if	(command[0] == '.' || command[0] == '/')
		return (handle_absolute_path(command));
	paths = ft_split(envp, ':');
	if (!paths)
		return (NULL);
	i = ft_countwords(envp, ':');
	while (--i >= 0)
	{
		ret = ft_pathjoin(paths[i], command);
		if (!ret)
			return (ft_splitfree(paths, i), NULL);
		if (access(ret, X_OK) == 0)
			return (ft_splitfree(paths, i + 1), ret);
		free(paths[i]);
		free(ret);
	}
	return (free(paths), ft_strdup("not_found"));
}

char	*env_get_by_name(char *name)
{
	t_envp	*head;

	head = *get_envp();
	while (head)
	{
		if (!ft_strncmp(head->name, name, ft_strlen(head->name))
			&& (ft_strlen(name) == ft_strlen(head->name)))
			return (head->value);
		head = head->next;
	}
	return (ft_strdup(""));
}
