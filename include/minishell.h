/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:13:37 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/24 09:04:47 by rchavez@stu      ###   ########.fr       */
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
int		count_lex(char *line);
t_lexer	*tokenize(char *line, char **args);
t_lexer	*token_fill(t_lexer *ret, char **args, char *line);
t_lexer	*fill_paths(t_lexer *ret, char **args, char *line);
void	free_tokens(t_lexer *tokens, char **args, char *line);
void	free_fail(t_lexer *tokens, char **args, char *line, int pos);


//utils
int		is_spc(char c);
int		is_op(char c);
char	**my_completion_function(const char *text, int start, int end);

//error handling
void	ft_error(int	errno);

//split
char	**ft_split_args(char *str);
char	**ft_splitfree(char **ret, size_t i);

//signals
void	signal_handler(void);
void	handle_ctrl_backslash(int signal);
void	handle_ctrlc(int signal);

//path
char	*path_finder(char *command, char *envp);

#endif