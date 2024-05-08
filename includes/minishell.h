/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:14:42 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/08 16:09:52 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/includes/libft.h"
//# include "builtins.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*env_element;
	char			*title;
	char			*info;
	int				index;
}	t_env;
typedef struct s_redir
{
	int				index;
	int				fd_out;
	int				fd_in;
	int				fd_status;
	char			*str;
	char			*filename;
	char			*cmd;
	char			*permissions;
	int				redir_type;
	struct s_redir	*next;

}	t_redir;
typedef struct s_args
{
	t_redir			**redirects;
	t_redir			**heredoc;
	int				is_hdoc;
	char			*arglist;
	char			**split_cmds;
	int				cmd_index;
	char			*tokenized_args;
	char			*long_command;
	int				redir_count;
	int				token_count;
	int				has_redir;
	pid_t			*pids;
	t_env			**envlist;
	int				is_builtin;
	int				**pipes;
}	t_args;

typedef struct s_input
{
	int		pipe_count;
	char	**input;
	t_args	**arg_struct;
	pid_t	*pids;
	t_env	**envlist;
	int		**pipes;
	int		pid_index;
}	t_input;

void	make_redirect_node(t_redir **redir, char *str, int len);
void	prep_input(char *line, t_input *input);
void	store_env(char **ep, t_env **env);
t_env	*get_last_node(t_env *env);
void	add_env_to_back(t_env **env, char *data, int index);
int		quotes_num(char *line);
void	parse_input(char **ep, t_env **env);
void	print_list(t_env *env);
// void	make_redir_node(char *input, t_redir **redir);
int		strlen_delim_double(char *str, char c, char k);
// void	scan_input(char *input, t_args *args);
// void	make_arg_node(char *input, t_args **args);
int		ft_arrlen(char **arr);
char	*trim_input(char *input, char c);
void	build_struct(t_input *input);
void	tokenize_args(t_args *args);
int		ft_is_redirect(char *str);
int		count_redirects(char *str);
char	*ft_strndup(char *str, size_t n, int flag);
void	clean_arglist(t_args *args);
void	update_redirs(t_args *args);
void	extract_cmds(t_args *args);
char	**copy_2d(char **src);
void	clean_redir_node(t_redir **redir, char *str);
char	*get_cmd_filename_last(char *str);
char	*get_file_filename_last(char *str);
char	*ft_getenv(t_env **envs, char *str);
void	prep_child_command(t_args *args);
int		valid_quotes(char *str);
int		valid_pipes(char *str);
int		valid_chars(char *str);
int		valid_redirect(char *str);
int		valid_sequence(char *str, char a, char b, char c);
char	**copy_env(char **ep, t_env **env);
void	store_env_title_n_info(t_env **env);
void	rl_replace_line(const char *text, int clear_undo);
void	free_content(t_env *env);
void	free_list(t_env **env);
void	prep_pids(t_input *input);
void	wait_for_children(t_input *input);
void	free_struct_content(t_args *args);
void	free_structs(t_args **structs, int pipecount);
void	free_input(t_input *input);
void	file_opening(t_redir *redir, t_args *args);
t_redir	*get_last_redir(t_redir *redir);
void	redir_fd_modifying(t_redir **redir);
int	cmd_is_builtin(t_env **envs, char **args);
#endif
