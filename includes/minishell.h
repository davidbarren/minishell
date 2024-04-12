/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:14:42 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/12 15:21:04 by dbarrene         ###   ########.fr       */
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
	char			**arglist;
	char			**split_cmds;
	int				cmd_index;
	struct s_args	*next;
}	t_args;

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*env_element;
	int				index;
}	t_env;

void	prep_input(char *input, t_args **args);
void	store_env(char **ep, t_env **env);
//t_env	*get_last_node(t_env *env);
void	add_env_to_back(t_env **env, char *data, int index);
void	parse_input(char **ep, t_env **env);
void	print_list(t_env *env);
void	make_redir_node(char *input, t_redir **redir);
int		strlen_delim(char *str, char c);
void	scan_input(char *input, t_args *args);
void	make_arg_node(char *input, t_args **args);
#endif
