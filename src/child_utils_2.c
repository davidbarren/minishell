/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:45:07 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/06 13:25:34 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	empty_check(t_args *args)
{
	if (args->long_command && !args->split_cmds[0])
	{
		free(args->long_command);
		free_2d(args->split_cmds);
		args->long_command = ft_strdup("   ");
		args->split_cmds = ft_split(args->long_command, 'a');
	}
}

int	builtin_vibecheck(t_redir **redirs)
{
	t_redir	*temp;

	temp = *redirs;
	while (temp)
	{
		if (!access(temp->str, F_OK))
		{
			if (access(temp->str, O_RDWR))
			{
				ft_printerror("🐒baboonshell: %s: Permission denied\n",
					temp->str);
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}
