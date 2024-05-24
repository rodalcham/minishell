# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 17:50:33 by lglauch           #+#    #+#              #
#    Updated: 2024/05/23 21:41:08 by rchavez@stu      ###   ########.fr        #
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
