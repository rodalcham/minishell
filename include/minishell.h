/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/13 12:40:47 by lglauch          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

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
}					t_file;

typedef struct s_lexer
{
	char			*path;
	char			**cmd;
	t_file			*input;
	t_file			*output;
	int				pid;
	struct s_lexer	*next;
}					t_lexer;

//helper values
int		*get_run(void);
t_envp	**get_envp(void);
int		*get_exit_status(void);

//t_lexer
t_lexer	*lex(char **args);
t_lexer	*init_lexer(int num);
int		count_lex(char **args);
void	handle_ops_open(t_lexer *lex, char **args, int *i);
char	**add_cmd(t_lexer *lex, char *str);

//files
t_file	*new_file(void);
void	set_file(t_file *file, char *file_n, int fd_n, int mode_n);

//io_handler
void	add_input(t_lexer *lex, char **args, int *i);
void	add_output(t_lexer *lex, char **args, int *i);
void	here_doc(t_lexer *lex, char **args, int *i);
void	add_pipe(t_lexer *lex);

//execute
void	execute(t_lexer *tokens);
void	exec_do(t_lexer *temp);

//utils
int		is_spc(char c);
int		is_op(char c);
char	*make_unclosed_quotes(char *str, int double_quotes, int single);
char	*handle_unclosed_quotes(char *str);

//utils2
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, size_t len);
char	*ft_strchr(const char *s, int c);

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

//builtins
int		echo_command(t_lexer *lexer);
int		write_and_check(int fd, const void *buf, size_t count);

#endif