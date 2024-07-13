# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 05:18:06 by rlabbiz           #+#    #+#              #
#    Updated: 2023/06/22 13:38:10 by rlabbiz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror 
OBJECT = minishell_ultis.o \
		 parser/lexar.o \
		 parser/lexar_quotes.o \
		 parser/analyzer.o \
		 parser/parser.o \
		 builtins/get_the_env.o \
		 builtins/builtins2.o \
		 builtins/builtins1.o \
		 builtins/utils_env.o \
		 builtins/main_builtins.o \
		 execution/exec.o \
		 execution/case_builtins.o \
		 parser/parser_ultis.o \
		 parser/redirection.o \
		 parser/herdoc.o \
		 parser/analyzer_ultis.o \
		 parser/lexar_quotes_ultis.o \
		 parser/expand.o \
		 parser/expand_utils.o \
		 parser/expand_utils1.o \
		 execution/exec_utils.o \
		 execution/exec_utils1.o 

MAIN_FILE = minishell.c
DEPS = minishell.h
LIBFT = libft/libft.a

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(LIBFT):
	@make bonus -C libft

$(NAME): $(MAIN_FILE) $(OBJECT) $(DEPS) $(LIBFT)
	@$(CC) $(CFLAGS) -L/Users/rlabbiz/.brew/opt/readline/lib -I /Users/rlabbiz/.brew/opt/readline/include -lreadline $(OBJECT) $(LIBFT) $(MAIN_FILE) -o $(NAME)
	@echo "\t The $(NAME) is created. "

# @$(CC) $(CFLAGS) -L/Users/ael-amin/.brew/opt/readline/lib -I /Users/ael-amin/.brew/opt/readline/include -lreadline $(OBJECT) $(LIBFT) $(MAIN_FILE) -o $(NAME)

.PHONY: all re clean fclean

clean:
	@rm -rf $(OBJECT)
	@make clean -C libft
	@echo "\t The object files is removed. "

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft
	@echo "\t The $(NAME) is removed. "

re: fclean all
