/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:32:09 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/05 13:47:53 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_pipes(t_input *input)
{
	int	i;
	int	fd;

	i = 0;
	if (input->pipe_count == 1)
		return ;
	input->pipes = ft_calloc(input->pipe_count - 1, sizeof (int *));
	if (!input->pipes)
		return ;
	while (i < input->pipe_count - 1)
	{
		input->pipes[i] = ft_calloc(2, sizeof (int));
		fd = pipe(input->pipes[i]);
		if (fd == -1)
		{
			ft_printerror("Pipes failed to open\n");
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
	if (!input->pipe_count)
		return ;
	while (input->pipe_count - 1 > i)
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

void	child_generic(t_input *input)
{
	int	status;
	int	limit;

	limit = input->pipe_count - 1;
	if (input->pid_index == 0 && input->pipe_count != 1)
	{
		child_first(input);
		dprintf(2, "in here\n");
		return ;
	}
	else if (input->pid_index == limit && input->pipe_count != 1)
	{
		child_last(input);
		dprintf(2, "in here child_last\n");
		return ;
	}
	else if (input->pipe_count > 1)
	{
		status = dup2(input->pipes[input->pid_index - 1][0], STDIN_FILENO);
		if (status == -1)
			ft_printerror("Error duping STDIN_FD\n");
		status = dup2(input->pipes[input->pid_index][1], STDOUT_FILENO);
		if (status == -1)
			ft_printerror("Error duping STDOUT\n");
	}
}

void	child_first(t_input *input)
{
	int	status;

	status = dup2(input->pipes[0][1], STDOUT_FILENO);
	if (status == -1)
		ft_printerror("failed to dup pipe and stdout in child 0\n");
}

void	child_last(t_input *input)
{
	int	status;

	status = dup2(input->pipes[input->pipe_count - 2][0], STDIN_FILENO);
	if (status == -1)
		ft_printerror("Failed to dup pipe and stdout in last child\n");
}
