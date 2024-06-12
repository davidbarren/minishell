/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:14:42 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/12 13:17:54 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/includes/libft.h"
//# include "builtins.h"
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_signal_exitstatus;

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
	char			*hdoc_title;
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
	int				is_echo;
	int				is_expanded;
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
	int				original_stdout;
	int				original_stdin;
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

typedef struct s_split_m
{
	char	**array;
	int		ar_i;
	int		i;
	int		j;
	char	temp;
	int		str_len;
	int		str_cnt;
}	t_split_m;

typedef struct s_clean
{
	int		i;
	int		j;
	char	c;
	char	*start;
	char	*copy;
}	t_clean;

// readline 
void	rl_replace_line(const char *text, int clear_undo);
// Inside main.c
void	free_struct_content(t_args *args);
void	free_structs(t_args **structs, int pipecount);
void	free_input(t_input *input);
void	baboonloop(t_input *input, struct termios tios);
// Inside initial_signals.c
void	initial_signals(void);
void	reset_termios(struct termios *tios);
void	modify_termios(struct termios *tios);
// Inside hdoc_signals.c
void	heredoc_signals(void);
void	reset_termios_hdoc(struct termios *tios);
void	modify_termios_hdoc(struct termios *tios);
void	heredoc_sigint(int signal);
void	check_g_exit_status(t_input *input);
// Inside exec_signals.c
void	exec_signals(void);
// Inside valid_syntax_check.c
int		syntax_validation(char *str);
// Inside valid_quotes.c
int		valid_quotes(char *str);
int		quote_count(char *str, char c);
// Inside valid_pipes.c
int		valid_pipes(char *str);
// Inside valid_chars.c
int		valid_chars(char *str);
int		valid_chars2(char *str);
// Inside valid_redirect.c
int		valid_redirect(char *str);
// Inside valid_sequence.c
int		valid_sequence(char *str, char a, char b, char c);
// Inside parsing.c
void	store_env(char **ep, t_env **env);
t_env	*get_last_node(t_env *env);
void	add_env_to_back(t_env **env, char *data, int index);
void	parse_input(char **ep, t_env **env);
void	print_list(t_env *env);
// Inside parsing_utils.c
void	store_env_title_n_info(t_env **env);
void	free_content(t_env *env);
void	free_list(t_env **env);
// Inside tokenizing.c
void	prep_input(char *line, t_input *input);
void	build_struct(t_input *input);
void	tokenize_input(t_input *input);
// Inside tokenized_utils.c
int		bad_syntax_post_expansion(char **tokenlist, int *exit_code);
void	free_and_null(char **str);
void	find_command(t_args *args, char **tokenlist);
int		emptystr_condition(char **tokenlist, int *exit_code);
// Inside tokenized_utils_2.c
void	alloc_and_make_redirs(char **tokenlist, t_args *args);
void	create_redir_node(char **tokenlist, t_redir **redirs, t_args *args);
int		vibecheck_dir(char **str, char *parsedstr);
// Inside token_utils.c
char	*ft_strndup(char *str, size_t n, int flag);
void	update_redirs(t_args *args);
// Inside token_utils_2.c
void	space_insertion(char *prepped, char *s, int i, int k);
int		ft_arrlen(char **arr);
t_redir	*get_last_redir(t_redir *redir);
// Inside token_utils_3.c
void	file_opening(t_redir *redir);
void	create_files(t_redir *temp, t_redir *output_node);
// Inside token_test.c
void	token_splitting(t_args *args, int *exit_code);
char	*prep_tokenizer(char *arglist, int redir_count);
int		redir_check(char *element);
void	make_redirect_node(t_redir **redir, char *str, int type, int index);
// Inside ft_expand.c
void	ft_expand(char **split_cmds, t_env **envlist, int es);
void	expand_check_arguments(t_env **envs, char **arg, int es);
// Inside ft_expand_utils1.c
void	space_parts(char *str, int *i, int *parts);
void	quote_redir_parts(char *str, int *i, int *parts, char *temp);
int		how_many_parts(char *str);
char	*get_beginning(char *str);
// Inside ft_expand_utils2.c
void	set_not_sup_char(char *str, int *i, int *len, char *c);
int		spacelen(char *str, int *i, int *len);
int		get_part_len(char *str, int i);
char	*is_expansion_valid(t_env **envs, char *arg, int i, int es);
int		get_qflag(char *arg);
// Inside ft_expand_utils3.c
void	expand_rest(t_env **envs, char **arg, int *i, int es);
char	*expand_key(t_env *node);
void	get_len_for_key(char *arg, int *i, int *len);
void	expand_qm(char **check, char **rest, int es);
int		compare_against_envs(t_env **envs, char **check, char **rest);
// Inside cmd_is_builtin.c
int		cmd_is_builtin(t_env **envs, char **args);
int		ft_strcmp_up_lo(char *s1, char *s2);
int		flag_for_builtin(char **args);
int		ft_is_emptystr(char *str);
// Inside ft_exit.c
void	ft_exit(char **args);
// Inside ft_cd.c
int		ft_cd(t_env **envs, char **cmd_args);
// Inside trim_input.c
char	*trim_input(char *input, char c);
// Inside ft_quoteclean.c
void	clean_expand_quotes(char **str);
// Inside ft_getenv.c
char	*ft_getenv(t_env **envs, char *str);
t_env	*getenv_node(t_env **envs, char *str);
// Inside forking.c
char	**copy_env(char **ep, t_env **env);
// Inside child_spawning.c
void	prep_pids(t_input *input);
void	prep_and_split_command(t_args *args, int *exit);
void	exec_child_cmd(t_input *input, int flag);
void	pipes_and_pids_allocation(t_input *input);
// Inside child_utils.c
void	wait_for_children(t_input *input);
void	check_path_access(t_args *args);
void	perms_check(t_args *args);
void	error_messages(t_input *input, int status, int index);
int		run_builtin(t_args *args);
// Inside child_utils_2.c
void	empty_check(t_args *args);
int		builtin_vibecheck(t_redir **redirs);
// Inside pipe_handling.c
void	child_generic(t_input *input);
void	open_pipes(t_input *input);
void	close_pipes(t_input *input);
void	child_first(t_input *input);
void	child_last(t_input *input);
// Inside redir_utils.c
void	redirs_iteration(t_redir **redirs, int has_cmd);
void	create_hdoc(t_redir *node);
// Inside redir_utils_2.c
void	store_original_fds(t_args *args);
void	free_redirs(t_redir **redirs);
t_redir	*get_last_hdoc(t_redir **redirs);
void	fetch_and_create_hdoc(t_args *args);
// Inside general_utils.c
void	restore_fds(t_args *args);
void	fd_routine_no_cmd(t_args *args);
int		cmd_is_echo(char *str);
int		ft_emptyline(char *line);
char	*ft_strdup_free(char *s);
// Inside loop_utils.c
void	input_valid_routine(t_input *input, char *line);
void	ft_update_shlvl(t_env **envs);
// Inside ft_split_mod.c
char	**ft_split_mod(char *str, char c);
// Should go inside cd utils
int		cd_badargs(char *str);
void	ft_gohome(t_env **envs);
int		condition_redirs(char **tokenlist, int *exit_code, char *parsed_string);
int		fake_file(char *str);
void	update_redir_quotehelper(t_args *args, int *i, char c);
#endif
