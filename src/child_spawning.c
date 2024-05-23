/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_spawning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:56:38 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/21 17:51:27 by plang            ###   ########.fr       */
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
		args->split_cmds = ft_split_mod(args->long_command, ' ');
	args->is_builtin = flag_for_builtin(args->split_cmds);
}

void	prep_and_split_command(t_args *args)
{
	int	i;

	// ft_expand(&args->arglist, args->envlist);
	// dprintf(2, "content of arglist in prep split:%s\n", args->arglist);
	i = 0;
	check_empty_and_split(args);
	// if (!args->is_empty)
		// ft_expand(args->split_cmds, args->envlist);
	while (args->split_cmds[i])
	{
		if (args->is_empty)
			args->split_cmds[i] = ft_strdup("");
		if (args->split_cmds[i][0] == '\"' && !args->is_empty)
			args->split_cmds[i] = trim_input(args->split_cmds[i], '\"');
		else if (args->split_cmds[i][0] == '\'' && !args->is_empty)
			args->split_cmds[i] = trim_input(args->split_cmds[i], '\'');
		i++;
	}
	if (args->pipecount == 1 && args->is_builtin)
	{
		args->split_path = NULL;
		args->execpath = NULL;
		cmd_is_builtin(args->envlist, args->split_cmds);
	}
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
	args->split_path = NULL;
	args->execpath = NULL;
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
	if (input->arg_struct[input->pid_index]->redir_count)
		file_opening(*input->arg_struct[input->pid_index]->redirects);
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
		free(args->execpath);
		check_path_access(args);
	}
}
