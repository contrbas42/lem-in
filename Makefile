# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otimofie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 11:59:13 by otimofie          #+#    #+#              #
#    Updated: 2018/04/18 11:59:15 by otimofie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS = ./work/main.c 

HEADER = lem-in.h

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRCS:.c=.o)
	
all: $(NAME)

$(OBJECTS): %.o: %.c
	@gcc -c $(CFLAGS) $< -o $@

$(NAME): $(OBJECTS)
	@make -C ../work/ft_printf
	@gcc $(CFLAGS) -I. $(SRCS) -L ./ft_printf -lftprintf -o $(NAME)
	@echo "\033[0;36mCompiled => [ $(NAME) ]\033[0m"

clean:
	@/bin/rm -f $(OBJECTS)
	@make clean -C ../work/ft_printf
	@echo "\033[0;31mDeleting => [ $(NAME) ]\033[0m"

fclean: clean
	@/bin/rm -f $(NAME) $(LIB)
	@make fclean -C ../work/ft_printf
	@echo "\033[0;31mFull Deleting => [ $(NAME) ]\033[0m"

re: fclean all
	@echo "\033[0;33mRedone => [ $(NAME) ]\033[0m"

.PHONY: all clean fclean re
