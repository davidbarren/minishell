/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:45:07 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/04 16:12:59 by dbarrene         ###   ########.fr       */
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
//		printf("contents of split_cmds after dumb check:%s\n", args->split_cmds[0]);
//		free_2d(args->split_path);
	}
}
