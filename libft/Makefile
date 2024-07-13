# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 08:56:14 by rlabbiz           #+#    #+#              #
#    Updated: 2023/06/21 21:35:45 by rlabbiz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGES = -Wall -Wextra -Werror
OBJECTS = ft_strlen.o ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_memset.o ft_bzero.o ft_strncmp.o ft_memchr.o ft_atoi.o ft_calloc.o ft_memcmp.o ft_memcpy.o ft_strchr.o ft_strdup.o ft_strjoin.o ft_strlcat.o ft_strlcpy.o ft_strnstr.o ft_substr.o ft_tolower.o ft_toupper.o ft_strtrim.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_split.o ft_strrchr.o ft_memmove.o ft_split.o ft_strmapi.o ft_striteri.o ft_itoa.o get_next_line.o ft_printf.o ft_putadd.o ft_putchr.o ft_puthex.o ft_putnbr.o ft_putstr.o ft_putnbr_unsigned.o
OBJECTS_BONUS = ft_lstnew_bonus.o ft_lstadd_back_bonus.o ft_lstadd_front_bonus.o ft_lstclear_bonus.o ft_lstdelone_bonus.o ft_lstiter_bonus.o ft_lstlast_bonus.o ft_lstsize_bonus.o 
DEPS = libft.h
CC = cc

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGES)

all: $(NAME)

$(NAME) : $(OBJECTS)
	@ar rsc $(NAME) $(OBJECTS)

.PHONY: clean fclean all re bonus

bonus: all $(NAME) $(OBJECTS_BONUS)
	@ar rsc $(NAME) $(OBJECTS_BONUS)

clean:
	@rm -rf *.o

fclean:
	@rm -rf *.o
	@rm -rf $(NAME)

re : fclean $(NAME)
	
