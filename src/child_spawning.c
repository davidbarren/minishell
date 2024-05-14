/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_spawning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:56:38 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/14 11:36:05 by dbarrene         ###   ########.fr       */
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
	while (i < input->pid_index)
	{
		waitpid(input->pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			printf("Exit status of child:%d\n", exit_code);
		}
		i++;
	}
}

void	prep_child_command(t_args *args)
{
	char	**ep;
	char	**split_path;
	int		i;
	char	*path;

	ep = NULL;
	i = 0;
	args->split_cmds = ft_quotesplit(args->long_command, ' ');
	while (args->split_cmds[i])
	{
		args->split_cmds[i] = trim_input(args->split_cmds[i], '\"');
		i++;
	}
	path = ft_getenv(args->envlist, "PATH");
	split_path = ft_split(path, ':');
	ep = copy_env(ep, args->envlist);
	i = 0;
	free (path);
	while (split_path[i])
	{
		split_path[i] = ft_strjoin_sep(split_path[i], args->split_cmds[0], '/');
		if (access(split_path[i], F_OK))
			i++;
		else
		{
			free(args->long_command);
			args->long_command = ft_strdup(split_path[i]);
			free_2d(split_path);
			if (execve(args->long_command, args->split_cmds, ep) == -1)
			{
				printf("execve has failed!\n");
				exit (127);
			}
		}
	}
	ft_printerror("Command not found!\n");
	free_2d(ep);
	if (split_path)
		free_2d(split_path);
}

void	prep_and_split_command(t_args *args)
{
	int	i;

	i = 0;
	args->envcpy = copy_env(args->envcpy, args->envlist);
	args->split_cmds = ft_quotesplit(args->long_command, ' ');
	args->is_builtin = flag_for_builtin(args->split_cmds);
	while (args->split_cmds[i])
	{
		args->split_cmds[i] = trim_input(args->split_cmds[i], '\"');
		args->split_cmds[i] = trim_input(args->split_cmds[i], '\'');
		printf("split command at index:%i is :%s\n", i, args->split_cmds[i]);
		i++;
	}
	if (args->pipecount == 1 && args->is_builtin)
		cmd_is_builtin(args->envlist, args->split_cmds);
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
	input->pid_index = 0;
	input->pids = calloc(input->pipe_count + 1, sizeof (pid_t));
	if (!input->pids)
		ft_printerror("allocation for PID array failed\n");
	while (input->pid_index < input->pipe_count)
	{
		input->pids[input->pid_index] = fork();
		if (input->pids[input->pid_index] == -1)
		{
			ft_printerror("Error forking and creating children at index:%d\n", input->pid_index);
			break ;
		}
		if (input->pids[input->pid_index] == 0)
		{
			printf("Hello from child at index:%d\n", input->pid_index);
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
			break ;
		}
		input->pid_index++;
	}
	wait_for_children(input);
}
