/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:26:44 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/06 21:36:36 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_for_children(t_input *input)
{
	int	i;
	int	status;
	int	exit_code;

	exit_code = 0;
	status = 0;
	i = 0;
	signal(SIGINT, SIG_IGN);
	exec_signals();
	while (i < input->pid_index)
	{
		waitpid(input->pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			input->exit_status = exit_code;
			error_messages(input, exit_code, i);
		}
		i++;
	}
	initial_signals();
	free(input->pids);
	free_2d(input->input);
}

void	error_messages(t_input *input, int status, int index)
{
	if (status == 127)
	{
		if (input->arg_struct[index]->split_cmds[0])
			ft_printerror("Baboonshell: %s: command not found\n",
				input->arg_struct[index]->split_cmds[0]);
	}
	if (status == 126)
	{
		if (input->arg_struct[index]->split_cmds[0])
			ft_printerror("Baboonshell: %s: is a directory\n",
				input->arg_struct[index]->split_cmds[0]);
	}
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

int	run_builtin(t_args *args)
{
	int	exit_status;

	args->split_path = NULL;
	args->execpath = NULL;
	if (args->redir_count)
	{
		store_original_fds(args);
		redirs_iteration(args->redirects, 1);
	}
	exit_status = cmd_is_builtin(args->envlist, args->split_cmds);
	if (args->redir_count)
		restore_fds(args);
	return (exit_status);
}
