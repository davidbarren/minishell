/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_spawning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:56:38 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/06 13:07:26 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_pipes(t_input *input)
{
	int	i;
	int	fd;

	i = 0;
	input->pipes = ft_calloc(input->pipe_count + 1, sizeof (int *));
	if (!input->pipes)
	{
		perror("Minishell malloc fail");
	}
	while (i <= input->pipe_count)
	{
		input->pipes[i] = malloc(2 * sizeof (int));
		fd = pipe(input->pipes[i]);
		if (fd == -1)
		{
			ft_printerror("Pipes failed to open\n");
			// free shit here
			// exit here
		}
		i++;
	}
}

void	close_pipes(t_input *input)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (input->pipe_count > i)
	{
		status = close(input->pipes[i][0]);
		if (status == -1)
			ft_printerror("Failed to open first end of pipe at index:%d\n", i);
		status = close(input->pipes[i][1]);
		if (status == -1)
			ft_printerror("Failed to open second end of pipe at index:%d\n", i);
		free(input->pipes[i++]);
	}
}

void	prep_pids(t_input *input)
{
	input->pid_index = 0;
	input->pids = calloc(input->pipe_count + 1, sizeof (pid_t));
	if (!input->pids)
		ft_printerror("allocation for PID array failed\n");
		//free shit and exit or something
	printf("Current pipecount in prep_pids:%d\n", input->pipe_count);
	while (input->pid_index < input->pipe_count)
	{
		input->pids[input->pid_index] = fork();
		if (input->pids[input->pid_index] == -1)
		{
			ft_printerror("Error forking and creating children at index:%d\n", input->pid_index);
			break ;
			//should put an error or something;
			//
		}
		if (input->pids[input->pid_index] == 0)
		{
			printf("Hello from child at index:%d\n", input->pid_index);
			prep_child_command(input->arg_struct[input->pid_index]);
			exit (69);
			break ;
		}
		printf("Contents of struct:%s\n at index:%d\n", input->arg_struct[input->pid_index]->long_command, input->pid_index);
		input->pid_index++;
	}
	wait_for_children(input);
	/*forking is somewhat functional, still scared to test more atm but seems to be going well with multiple
	cmds*/
}

void	wait_for_children(t_input *input)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < input->pid_index)
		waitpid(input->pids[i++], &status, 0);
	// probably need to start freeing here;
}
