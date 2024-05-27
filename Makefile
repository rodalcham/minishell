# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/05/27 11:46:15 by rchavez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CFLAGS	:= -Wextra -Wall -Werror
CFLAGS	:= -Wextra -Wall -Werror -I/usr/local/opt/readline/include
SRCS	:= src/main.c src/globals.c src/utils.c src/ft_split_args.c src/tokenize.c src/signals.c src/path.c\
			libft/ft_split.c libft/ft_strlen.c libft/ft_strncmp.c src/free_tokens.c src/ft_error.c
OBJS	:= ${SRCS:src/%.c=src/%.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ libft/libft.a -lreadline 

src/%.o: src/%.c
	@make -C libft
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make -C libft clean
	rm -rf src/*.o

fclean: clean
	@make -C libft fclean
	rm -rf $(NAME)

re: clean all

debug: CFLAGS += -g -O0
debug: fclean $(NAME)

run: $(NAME) 
	./minishell
