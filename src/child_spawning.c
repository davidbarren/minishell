/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_spawning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:56:38 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/17 11:09:49 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_and_split_command(t_args *args)
{
	int	i;

	i = 0;
	args->envcpy = copy_env(args->envcpy, args->envlist);
	args->split_cmds = ft_quotesplit(args->long_command, ' ');
	args->is_builtin = flag_for_builtin(args->split_cmds);
	//expansion function goes here :)!
	while (args->split_cmds[i])
	{
		if (args->split_cmds[i][0] == '\"')
			args->split_cmds[i] = trim_input(args->split_cmds[i], '\"');
		else if (args->split_cmds[i][0] == '\'')
			args->split_cmds[i] = trim_input(args->split_cmds[i], '\'');
		i++;
	}
	if (args->pipecount == 1 && args->is_builtin)
		cmd_is_builtin(args->envlist, args->split_cmds);
	if (!args->is_builtin)
		perms_check(args);
}

void	check_path_access(t_args *args)
{
	int	i;

	i = 0;
	while (args->split_path[i])
	{
		args->split_path[i] = ft_strjoin_sep(args->split_path[i],
				args->split_cmds[0], '/');
		if (!access(args->split_path[i], F_OK))
		{
			if (!access(args->split_path[i], X_OK))
			{
				args->execpath = ft_strdup(args->split_path[i]);
				return ;
			}
		}
		if (access(args->split_path[i], F_OK))
			i++;
	}
	free_2d(args->split_path);
}

void	prep_pids(t_input *input)
{
	open_pipes(input);
	input->pid_index = 0;
	input->pids = calloc(input->pipe_count + 1, sizeof (pid_t));
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
	if (input->arg_struct[input->pid_index]->redir_count)
		file_opening(*input->arg_struct[input->pid_index]->redirects);
	if (input->arg_struct[input->pid_index]->is_builtin)
	{
		input->arg_struct[input->pid_index]->builtinstatus
			= (cmd_is_builtin(input->arg_struct[input->pid_index]->envlist,
					input->arg_struct[input->pid_index]->split_cmds));
		exit (input->arg_struct[input->pid_index]->builtinstatus);
	}
	execve(input->arg_struct[input->pid_index]->execpath,
		input->arg_struct[input->pid_index]->split_cmds,
		input->arg_struct[input->pid_index]->envcpy);
	exit (127);
}

void	perms_check(t_args *args)
{
	if (!args->is_builtin)
	{
		if (!access(args->split_cmds[0], F_OK))
		{
			if (!access(args->split_cmds[0], X_OK))
			{
				args->execpath = ft_strdup(args->split_cmds[0]);
				return ;
			}
		}
		args->execpath = ft_getenv(args->envlist, "PATH");
		if (!args->execpath)
			return ;
		args->split_path = ft_split(args->execpath, ':');
		check_path_access(args);
	}
}
