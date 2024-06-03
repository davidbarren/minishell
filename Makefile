# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plang <plang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 14:15:56 by dbarrene          #+#    #+#              #
#    Updated: 2024/06/03 19:15:34 by dbarrene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC	= cc
CFLAGS = -Wall -Wextra -g -Werror #-fsanitize=address 

SRCDIR = src
OBJDIR = obj
LIBFTPATH = libft

READUTILS = -I ~/.brew/Cellar/readline/8.2.10/include

READLINE = -L ~/.brew/Cellar/readline/8.2.10/lib/ -lreadline 

HEADERS = -I ./includes

LIBFT = $(LIBFTPATH)/libft.a

SRCS = $(SRCDIR)/main.c\

BSRCS = $(SRCDIR)/main_bonus.c\

CSRCS = $(SRCDIR)/parsing.c\
		$(SRCDIR)/tokenizing.c\
		$(SRCDIR)/trim_input.c\
		$(SRCDIR)/token_utils.c\
		$(SRCDIR)/token_utils_2.c\
		$(SRCDIR)/token_utils_3.c\
		$(SRCDIR)/forking.c\
		$(SRCDIR)/ft_getenv.c\
		$(SRCDIR)/cmd_is_builtin.c\
		$(SRCDIR)/ft_echo.c\
		$(SRCDIR)/ft_env.c\
		$(SRCDIR)/ft_export.c\
		$(SRCDIR)/ft_export_utils1.c\
		$(SRCDIR)/ft_export_utils2.c\
		$(SRCDIR)/ft_pwd.c\
		$(SRCDIR)/ft_unset.c\
		$(SRCDIR)/ft_cd.c\
		$(SRCDIR)/ft_exit.c\
		$(SRCDIR)/valid_chars.c\
		$(SRCDIR)/valid_quotes.c\
		$(SRCDIR)/valid_redirect.c\
		$(SRCDIR)/valid_pipes.c\
		$(SRCDIR)/valid_sequence.c\
		$(SRCDIR)/valid_syntax_check.c\
		$(SRCDIR)/parsing_utils.c\
		$(SRCDIR)/child_spawning.c\
		$(SRCDIR)/child_utils.c\
		$(SRCDIR)/child_utils_2.c\
		$(SRCDIR)/pipe_handling.c\
		$(SRCDIR)/ft_expand.c\
		$(SRCDIR)/token_test.c\
		$(SRCDIR)/redir_utils.c\
		$(SRCDIR)/redir_utils_2.c\
		$(SRCDIR)/tokenized_utils.c\
		$(SRCDIR)/ft_split_mod.c\
		$(SRCDIR)/general_utils.c\

OBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BOBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(BSRCS))
COBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSRCS))

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJDIR) $(COBJS) $(OBJS)
	@echo $(NAME) is being compiled...
	@$(CC) $(CFLAGS) $(OBJS) $(COBJS) -L$(LIBFTPATH) $(HEADERS) $(READUTILS) $(READLINE) -lft -o $(NAME) 

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
