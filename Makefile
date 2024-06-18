# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 17:50:33 by lglauch           #+#    #+#              #
#    Updated: 2024/06/18 12:50:47 by rchavez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS	:= -Wextra -Wall -Werror

CC := cc

LIB := libftnew

LIBFT := libftnew/libft.a

SRCS	:= src/main.c src/globals.c src/utils.c src/ft_split_args.c\
src/signals.c src/path.c src/ft_error.c src/utils2.c src/envp.c src/expand.c\
src/t_lexer.c src/t_file.c src/io_handler.c src/execute.c src/free_all.c\
src/get_line.c src/heredoc.c src/builtins/cd.c src/builtins/check_builtins.c\
src/builtins/echo.c src/builtins/env.c src/builtins/export.c\
src/builtins/pwd.c src/builtins/unset.c src/builtins/exit.c

OBJS	:= ${SRCS:src%.c=obj%.o}

OBJ_F := obj

all:$(OBJ_F) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT) : $(LIB)
	cd $(LIB) && make

$(LIB) : 
	@touch .gitmodules
	@git submodule add -f https://github.com/lglauch/libftnew.git
	
$(OBJ_F) : 
	@mkdir obj
	@mkdir obj/builtins

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	cd $(LIB) && make clean
	rm -rf $(OBJ_F)

fclean: clean
	rm -rf $(LIB)
	rm -rf $(NAME)

re: clean all

debug: CFLAGS += -g -O0
debug: fclean $(NAME)

run: all
	./minishell

PHONY : all, clean, fclean, re, run
