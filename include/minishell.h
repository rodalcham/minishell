/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:13:37 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/10 12:21:27 by rchavez          ###   ########.fr       */
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

# define READ O_RDONLY
# define WRITE (O_WRONLY | O_TRUNC | O_CREAT)
# define APPEND (O_WRONLY | O_CREAT | O_APPEND)
// # define HEREDOC 
# define PERMISSIONS 0644


typedef struct s_envp
{
	char			*value;
	char			*name;
	struct s_envp	*next;
}					t_envp;

typedef struct s_file
{
	char			*filename;
	int				mode;
	int				fd;
	struct s_file	*next;
}					t_file;

typedef struct s_lexer
{
	char			*path;
	char			**cmd;
	t_file			*input;
	t_file			*output;
	char **ops;
	struct s_lexer	*next;
}					t_lexer;

//fake globals
int		*get_run(void);
t_envp	**get_envp(void);

//tokens
int		count_lex_t(char *line);
t_lexer	*tokenize(char *line, char **args);
t_lexer	*token_fill(t_lexer *ret, char **args, char *line);
t_lexer	*fill_paths(t_lexer *ret, char **args, char *line);
void	free_tokens(t_lexer *tokens, char **args, char *line);
void	free_fail(t_lexer *tokens, char **args, char *line, int pos);

//t_lexer
t_lexer	*lex(char **args);
t_lexer	*init_lexer(int num);
int		count_lex(char **args);
void	handle_ops_open(t_lexer *lex, char **args, int *i);

//files
t_file	*new_file(t_file *head);
void	set_file(t_file *file, char *file_n, int fd_n, int mode_n);

//io_handler
void	add_input(t_lexer *lex, char **args, int *i);
void	add_output(t_lexer *lex, char **args, int *i);
void	here_doc(t_lexer *lex, char **args, int *i);

//utils
int		is_spc(char c);
int		is_op(char c);
char	*make_unclosed_quotes(char *str, int double_quotes, int single);
char	*handle_unclosed_quotes(char *str);

//utils2
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, size_t len);

//error handling
void	ft_error(int errno);

//split
char	**ft_split_args(char *str);
char	**ft_splitfree(char **ret, size_t i);

//signals
void	signal_handler(void);
void	handle_ctrlc(int signal);

//path
char	*path_finder(char *command, char *envp);
char	*env_get_by_name(char *name);

//envp
t_envp	*ft_create_envp(char **envp);
void	ft_free_envp(t_envp *head);

//expand
char	*expand_tokens(char *str);

#endif