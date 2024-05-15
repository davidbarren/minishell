/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:32:09 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/15 11:56:59 by dbarrene         ###   ########.fr       */
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
/*
void	child_generic(t_input *input)
{

}*/
