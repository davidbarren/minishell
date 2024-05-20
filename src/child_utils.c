/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:26:44 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/20 11:35:31 by dbarrene         ###   ########.fr       */
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
			input->exit_status = exit_code;
			error_messages(input, exit_code, i);
			ft_printerror("exit status of child:%d\n", input->exit_status);
		}
		i++;
	}
}

void	error_messages(t_input *input, int status, int index)
{
	if (status == 127)
	{
		if (input->arg_struct[index]->split_cmds[0])
			ft_printerror("Baboonshell: %s: command not found\n",
			input->arg_struct[index]->split_cmds[0]);
		else
			ft_printerror("Baboonshell: : command not found\n");
	}
}
