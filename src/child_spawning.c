/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_spawning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:56:38 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/25 17:24:19 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_empty_and_split(t_args *args)
{
	int	i;

	i = 0;
	args->envcpy = copy_env(args->envcpy, args->envlist);
	args->is_empty = ft_is_emptystr(args->long_command);
	if (args->is_empty)
		args->split_cmds = ft_split(args->long_command, '\"');
	else
	{
		args->split_cmds = ft_split_mod(args->long_command, ' ');
		args->is_echo = cmd_is_echo(args->split_cmds[0]);
	}
	while (args->split_cmds[i] && !args->is_echo)
	{
		clean_expand_quotes(&args->split_cmds[i]);
		i++;
	}
	args->is_builtin = flag_for_builtin(args->split_cmds);
	empty_check(args);
}

void	prep_and_split_command(t_args *args, int *exit)
{
	if (!args->long_command)
		return ;
	check_empty_and_split(args);
	if (args->pipecount == 1 && args->is_builtin && args->long_command)
	{
		*exit = run_builtin(args);
	}
	if (!args->is_builtin && args->long_command)
		perms_check(args);
}

void	prep_pids(t_input *input)
{
	pipes_and_pids_allocation(input);
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
			signal(SIGINT, SIG_DFL);
			child_generic(input);
			close_pipes(input);
			if (input->arg_struct[input->pid_index]->split_cmds)
				cmd_is_dir(input->arg_struct[input->pid_index]->split_cmds[0]);
			exec_child_cmd(input, 1);
			exit (127);
		}
		input->pid_index++;
	}
	close_pipes(input);
	wait_for_children(input);
}

void	exec_child_cmd(t_input *input, int flag)
{
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
		execve(input->arg_struct[input->pid_index]->execpath,
			input->arg_struct[input->pid_index]->split_cmds,
			input->arg_struct[input->pid_index]->envcpy);
	}
	exit (127);
}

void	pipes_and_pids_allocation(t_input *input)
{
	open_pipes(input);
	input->pid_index = 0;
	input->pids = ft_calloc(input->pipe_count + 1, sizeof (pid_t));
	if (!input->pids)
		ft_printerror("allocation for PID array failed\n");
}
