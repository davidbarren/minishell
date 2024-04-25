# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plang <plang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 14:15:56 by dbarrene          #+#    #+#              #
#    Updated: 2024/04/24 09:48:37 by dbarrene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC	= cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address 

SRCDIR = src
OBJDIR = obj
LIBFTPATH = libft

READUTILS = -I ~/.brew/Cellar/readline/8.2.10/include

READLINE = -L ~/.brew/Cellar/readline/8.2.10/lib/ -lreadline 

LIBFT = $(LIBFTPATH)/libft.a

SRCS = $(SRCDIR)/main.c\

BSRCS = $(SRCDIR)/main_bonus.c\

CSRCS = $(SRCDIR)/parsing.c\
		$(SRCDIR)/tokenizing.c\
		$(SRCDIR)/trim_input.c\
		$(SRCDIR)/token_utils.c\
		$(SRCDIR)/token_utils_2.c\

OBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BOBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(BSRCS))
COBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSRCS))

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJDIR) $(COBJS) $(OBJS)
	@echo $(NAME) is being compiled...
	$(CC) $(CFLAGS) $(OBJS) $(COBJS) -L$(LIBFTPATH) $(READUTILS) $(READLINE) -lft -o $(NAME) 

$(LIBFT):
	@make -C $(LIBFTPATH)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

bonus: .bonus

.bonus: $(LIBFT) $(OBJDIR) $(BOBJS) $(BSRCS) $(COBJS) $(OBJS)
	@echo $(NAME) is being compiled with bonuses...
	@$(CC) $(CFLAGS) $(COBJS) $(BOBJS) -L$(LIBFTPATH) -lft -o $(NAME)
	@touch .bonus

clean:
	@make -C $(LIBFTPATH) clean
	@rm -rf $(OBJDIR)
	@echo Removed Objs

fclean: clean
	@make -C $(LIBFTPATH) fclean
	@rm -rf $(NAME)
	@echo Removed $(NAME)
re: fclean all
