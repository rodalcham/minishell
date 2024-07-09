/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:13:59 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/09 16:54:40 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		update_cwd(void);
int		update_ocwd(void);
void	cd_expand_home(t_lexer *lexer, char path[], int *i);
void	cd_expand_old(t_lexer *lexer, char path[], int *i);

void	do_cd(char path[], int *i)
{
	if (chdir(path) == -1)
	{
		ft_perror("cd: ", path, ": No such file or directory\n");
		*get_exit_status() = 1;
	}
	else
		*get_exit_status() = 0;
	if (*get_exit_status() == 0 && *i == 2)
		printf("%s\n", path);
}

int	cd_command(t_lexer *lexer)
{
	char	path[4096];
	int		i;

	i = 0;
	if (lexer->next || *get_lexer() != lexer)
		return (0);
	cd_expand_home(lexer, path, &i);
	cd_expand_old(lexer, path, &i);
	if (update_ocwd() < 0)
		return (-1);
	if (!i && lexer->cmd[1])
		ft_strlcpy(path, lexer->cmd[1], 4096);
	if (i >= 0)
	{
		do_cd(path, &i);
	}
	if (update_cwd() < 0)
		return (-1);
	return (*get_exit_status());
}
