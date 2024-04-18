# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plang <plang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 10:40:52 by dbarrene          #+#    #+#              #
#    Updated: 2024/04/18 18:10:35 by dbarrene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DIR = obj

VPATH = gnl:ft_printf:libft:ft_printerror

SRC = \
ft_bzero.c				ft_isalnum.c		ft_isalpha.c	ft_isascii.c 		\
ft_isdigit.c			ft_isprint.c		ft_memcpy.c		ft_memmove.c 		\
ft_memset.c				ft_memchr.c			ft_memcmp.c		ft_strlcpy.c 		\
ft_strlen.c				ft_strncmp.c		ft_tolower.c	ft_toupper.c		\
ft_calloc.c				ft_putchar_fd.c		ft_putstr_fd.c	ft_putendl_fd.c 	\
ft_strchr.c				ft_strrchr.c		ft_strdup.c		ft_strlcat.c		\
ft_strnstr.c			ft_atoi.c			ft_substr.c		ft_strjoin.c		\
ft_strtrim.c			ft_putnbr_fd.c		ft_itoa.c		ft_strmapi.c		\
ft_striteri.c			ft_split.c			ft_format_check.c	ft_iterate_format.c		\
ft_printf.c				ft_put_hex.c		ft_put_ptr.c		ft_put_unsigned.c	\
ft_putchar_mod.c		ft_putnbr_mod.c	ft_putstr_mod.c			\
get_next_line.c			get_next_line_utils.c\
ft_put_hex_error.c\
ft_format_check_error.c\
ft_iterate_format_error.c\
ft_printerror.c\
ft_put_ptr_error.c\
ft_put_unsigned_error.c\
ft_putchar_mod_error.c\
ft_putnbr_mod_error.c\
ft_putstr_mod_error.c\
ft_substring.c\
ft_newsplit.c\
free_2d.c\
ft_strjoin_flex.c\
ft_skipchar.c\

CFLAGS = -Wall -Wextra -Werror -g
INCFLAGS = -Iincludes

DEP = $(OBJ:.o=.d)

all:  $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) $(INCFLAGS) -c $< -o $@

-include $(DEP)

clean:
	@rm -rf $(OBJ_DIR) 

fclean: clean
	@rm -f $(NAME)
re: fclean all
