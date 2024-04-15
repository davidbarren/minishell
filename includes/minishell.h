/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:14:42 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/15 13:40:45 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_redir
{
	int				index;
	int				fd_out;
	int				fd_in;
	char			*str;
	struct s_redir	*next;

}	t_redir;
typedef struct s_args
{
	t_redir			**redirects;
	t_redir			**heredoc;
	char			*arglist;
	char			**split_cmds;
	int				cmd_index;
}	t_args;

typedef struct s_input
{
	int		pipe_count;
	char	**input;
	t_args	**arg_struct;
}	t_input;

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*env_element;
	int				index;
}	t_env;

void	prep_input(char *line, t_input *input);
void	store_env(char **ep, t_env **env);
//t_env	*get_last_node(t_env *env);
void	add_env_to_back(t_env **env, char *data, int index);
void	parse_input(char **ep, t_env **env);
void	print_list(t_env *env);
// void	make_redir_node(char *input, t_redir **redir);
int		strlen_delim(char *str, char c);
// void	scan_input(char *input, t_args *args);
// void	make_arg_node(char *input, t_args **args);
int		ft_arrlen(char **arr);
char	*trim_input(char *input, char c);
#endif
