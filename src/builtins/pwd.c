/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:05 by leo               #+#    #+#             */
/*   Updated: 2024/06/21 11:17:58 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_command(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("pwd: error retrieving current directory\n");
		return (1);
	}
	printf("%s\n", path);	
	free(path);
	return (0);
}
