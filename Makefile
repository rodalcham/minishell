# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 17:50:33 by lglauch           #+#    #+#              #
#    Updated: 2024/06/26 10:12:18 by rchavez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS	:= -Wextra -Wall -Werror

CC := cc

LIB := libftnew

MLIB := ft_malloc

LIBFT := libftnew/libft.a

MFT := ft_malloc/ft_malloc.a

SRCS	:= src/main.c src/globals.c src/utils.c src/ft_split_args.c\
src/signals.c src/path.c src/ft_error.c src/utils2.c src/envp.c src/expand.c\
src/t_lexer.c src/t_file.c src/io_handler.c src/execute.c src/free_all.c\
src/get_line.c src/heredoc.c src/builtins/cd.c src/builtins/check_builtins.c\
src/builtins/echo.c src/builtins/env.c src/builtins/export.c\
src/builtins/pwd.c src/builtins/unset.c src/builtins/exit.c src/helper.c\

OBJS	:= ${SRCS:src%.c=obj%.o}

OBJ_F := obj

OBJ_FB := obj/builtins

all: $(OBJ_FB) $(NAME)

$(NAME): $(LIBFT) $(MFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MFT) -lreadline

$(LIBFT) : $(LIB)
	cd $(LIB) && make

$(LIB) : 
	@touch .gitmodules
	@git submodule add -f https://github.com/lglauch/libftnew.git

$(MFT) : $(MLIB)
	cd $(MLIB) && make

$(MLIB) :
	@touch .gitmodules
	@git submodule add -f https://github.com/rodalcham/ft_malloc.git
	
$(OBJ_F) : 
	@if [ ! -d $(OBJ_F) ]; then \
		mkdir $(OBJ_F); \
	fi

$(OBJ_FB) : $(OBJ_F)
	@if [ ! -d $(OBJ_FB) ]; then \
		mkdir $(OBJ_FB); \
	fi

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@if [ -d "$(LIB)" ]; then \
		cd $(LIB) && make clean; \
	else \
		echo "Directory '$(LIB)' cannot be cleaned"; \
	fi
	@if [ -d "$(MLIB)" ]; then \
		cd $(MLIB) && make clean; \
	else \
		echo "Directory '$(MLIB)' cannot be cleaned"; \
	fi
	rm -rf $(OBJ_F)

fclean: clean
	@if [ -d "$(LIB)" ]; then \
		rm -fr $(LIB); \
	else \
		echo "Directory '$(LIB)' cannot be removed."; \
	fi
	@if [ -d "$(MLIB)" ]; then \
		rm -fr $(MLIB); \
	else \
		echo "Directory '$(MLIB)' cannot be removed."; \
	fi
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS += -g -O0
debug: fclean all

run: all
	./minishell

PHONY : all, clean, fclean, re, run
