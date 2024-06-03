/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_spawning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:56:38 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/30 02:36:00 by dbarrene         ###   ########.fr       */
/*   Updated: 2024/05/28 16:16:03 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_fds(t_args *args)
{
	dup2(args->original_stdin, STDIN_FILENO);
	close(args->original_stdin);
	dup2(args->original_stdout, STDOUT_FILENO);
	close(args->original_stdout);
}

int		cmd_is_echo(char *str)
{
	if (ft_strcmp_up_lo(str, "echo"))
		return 0;
	return 1;
}

void	check_empty_and_split(t_args *args)
{
	int	i;

	i = 0;
	args->envcpy = copy_env(args->envcpy, args->envlist);
	args->is_empty = ft_is_emptystr(args->long_command);
	if (args->is_empty)
		args->split_cmds = ft_split(args->long_command, '\"');
	else
		args->split_cmds = ft_split_mod(args->long_command, ' ');
	args->is_echo = cmd_is_echo(args->split_cmds[0]);
	while (args->split_cmds[i] && !args->is_echo)
	{	
		dprintf(2, "content of split cmds before trim:%s\n", args->split_cmds[i]);
//		if (*args->split_cmds[i] == '\'')
//			args->split_cmds[i] = trim_input(args->split_cmds[i], '\'');
//		else if (*args->split_cmds[i] == '\"')
			clean_expand_quotes(&args->split_cmds[i]);
//			clean_echo_from_quotes(&args->split_cmds[i]);
//			args->split_cmds[i] = trim_input(args->split_cmds[i], '\"');
		dprintf(2, "content of split cmds after trim:%s\n", args->split_cmds[i]);
		i++;
	}
	args->is_builtin = flag_for_builtin(args->split_cmds);
}

void	prep_and_split_command(t_args *args)
{
	int	i;

	i = 0;
//	dprintf(2, "content of long cmd:%s\n", args->long_command);
	if (!args->long_command)
		return ;
	check_empty_and_split(args);
	dprintf(2," about to enter is builtin check for trimming\n");
	dprintf(2," status of is echo:%d\n", args->is_echo);
//	while (args->split_cmds[i] && !args->is_echo)
//	{	
//		dprintf(2, "content of split cmds before trim:%s\n", args->split_cmds[i]);
//		args->split_cmds[i] = trim_input(args->split_cmds[i], '"');
//	 //	ft_strtrim(args->split_cmds[i], "\"");
//		dprintf(2, "content of split cmds after trim:%s\n", args->split_cmds[i]);
//		i++;
//	}
  // quotes should be trimmed here
	if (args->pipecount == 1 && args->is_builtin && args->long_command)
		run_builtin(args);
	if (!args->is_builtin && args->long_command)
		perms_check(args);
}

void	prep_pids(t_input *input)
{
	open_pipes(input);
	input->pid_index = 0;
	input->pids = ft_calloc(input->pipe_count + 1, sizeof (pid_t));
	if (!input->pids)
		ft_printerror("allocation for PID array failed\n");
	while (input->pid_index < input->pipe_count)
	{
		input->pids[input->pid_index] = fork();
		if (input->pids[input->pid_index] == -1)
		{
			ft_printerror("Error forking at index:%d\n", input->pid_index);
			break ;
		}
		if (input->pids[input->pid_index] == 0)
		{
			child_generic(input);
			close_pipes(input);
			exec_child_cmd(input);
			break ;
		}
		input->pid_index++;
	}
	close_pipes(input);
	wait_for_children(input);
}

void	exec_child_cmd(t_input *input)
{
	int	flag;

	flag = 1;
	store_original_fds(input->arg_struct[input->pid_index]);
	if (!input->arg_struct[input->pid_index]->long_command)
		flag = 0;
	if (input->arg_struct[input->pid_index]->redir_count)
	{
		restore_fds(input->arg_struct[input->pid_index]);
		redirs_iteration(input->arg_struct[input->pid_index]->redirects, flag);
	}
	if (!input->arg_struct[input->pid_index]->long_command)
		return ;
	if (input->arg_struct[input->pid_index]->is_builtin)
	{
		input->arg_struct[input->pid_index]->builtinstatus
			= (cmd_is_builtin(input->arg_struct[input->pid_index]->envlist,
					input->arg_struct[input->pid_index]->split_cmds));
		exit (input->arg_struct[input->pid_index]->builtinstatus);
	}
	if (input->arg_struct[input->pid_index]->split_cmds[0])
	{
//		dprintf(2,"path sent to execve:%s\n",input->arg_struct[input->pid_index]->execpath);
//		int k = 0;
//		while (input->arg_struct[input->pid_index]->split_cmds[k])
//			dprintf(2,"split cmds sent to execve:%s\n",input->arg_struct[input->pid_index]->split_cmds[k++]);
		execve(input->arg_struct[input->pid_index]->execpath,
			input->arg_struct[input->pid_index]->split_cmds,
			input->arg_struct[input->pid_index]->envcpy);
	}
	exit (127);
}
