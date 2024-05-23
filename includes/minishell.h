/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:14:42 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/23 13:42:29 by dbarrene         ###   ########.fr       */
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
	int				fd;
	char			*str;
	char			*filename;
	char			*cmd;
	char			*permissions;
	char			*input;
	char			*output;
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
	int				index;
	int				is_empty;
	char			*tokenized_args;
	char			*long_command;
	int				redir_count;
	int				token_count;
	int				has_redir;
	pid_t			*pids;
	t_env			**envlist;
	int				is_builtin;
	int				**pipes;
	int				pipecount;
	int				builtinstatus;
	char			**split_path;
	char			*execpath;
	char			**envcpy;
	char			*input;
	char			*output;
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
	int		exit_status;
}	t_input;

void	make_redirect_node(t_redir **redir, char *str, int type);
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
int		valid_chars2(char *str);
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
void	file_opening(t_redir *redir);
t_redir	*get_last_redir(t_redir *redir);
void	redir_fd_modifying(t_redir **redir);
int		cmd_is_builtin(t_env **envs, char **args);
int		ft_strcmp_up_lo(char *s1, char *s2);
void	check_path_access(t_args *args);
void	prep_and_split_command(t_args *args);
int		syntax_validation(char *str);
int		flag_for_builtin(char **args);
int		ft_cd(t_env **envs, char **cmd_args);
void	exec_child_cmd(t_input *input);
void	sanitize_input(t_input *input);
void	perms_check(t_args *args);
void	baboonloop(t_input *input);
void	create_files(t_redir *temp, t_redir *output_node);
void	child_generic(t_input *input);
void	open_pipes(t_input *input);
void	close_pipes(t_input *input);
void	child_first(t_input *input);
void	child_last(t_input *input);
void	error_messages(t_input *input, int status, int index);
void	ft_expand(char **split_cmds, t_env **envlist);
void	baboon_free(char **stackarr);
int		ft_is_emptystr(char *str);
void	make_tokens(t_args *args);
void	token_splitting(t_args *args);
void	redirs_iteration(t_redir **redirs);
int		redir_check(char *element);
void	space_insertion(char *prepped, char *source);
void	find_command(t_args *args, char **tokenlist);
char 	**ft_split_mod(char *str, char c);
#endif
