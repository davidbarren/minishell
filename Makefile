# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plang <plang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 14:15:56 by dbarrene          #+#    #+#              #
#    Updated: 2024/04/18 16:35:31 by dbarrene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC	= cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address 

SRCDIR = src
OBJDIR = obj
LIBFTPATH = libft

READLINE = -lreadline -L ~/.brew/opt/readline/lib

READUTILS = -I ~/.brew/opt/readline/include

LIBFT = $(LIBFTPATH)/libft.a

SRCS = $(SRCDIR)/main.c\

BSRCS = $(SRCDIR)/main_bonus.c\

CSRCS = $(SRCDIR)/parsing.c\
		$(SRCDIR)/tokenizing.c\
		$(SRCDIR)/trim_input.c\
		$(SRCDIR)/token_utils.c\

OBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BOBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(BSRCS))
COBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJDIR) $(COBJS) $(OBJS)
	@echo $(NAME) is being compiled...
	$(CC) $(CFLAGS) $(OBJS) $(COBJS) -L$(LIBFTPATH) $(READUTILS) -lft -o $(NAME) $(READLINE) 

$(LIBFT):
	@make -C $(LIBFTPATH)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

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
