/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:13:37 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/19 15:07:16 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <unistd.h>

// typedef struct s_lexer
// {
// 	s_lexer	*next;
// 	s_lexer	*previous;
// 	int		index;
// 	char	**str;
// }		t_lexer;

typedef struct s_lexer
{
	char			*path;
	char			**cmd;
	char			**ops;
}					t_lexer;

//signals
int		*get_run(void);

//tokens
char	**tokenizer(char *line);
t_lexer	*tokenize(char *line);
int	count_lex(char *line);
t_lexer	*token_fill(t_lexer *ret, char **args);

//utils
void	*ft_realloc(void *ptr, size_t size);

//split
char	**ft_split_args(char *str);

//signals
void	signal_handler(void);
void	handle_ctrl_backslash(int signal);
void	handle_ctrlc(int signal);

#endif