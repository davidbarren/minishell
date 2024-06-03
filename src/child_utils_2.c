/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:45:07 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/03 19:22:38 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	empty_check(t_args *args)
{
	if (args->long_command && !args->split_cmds[0])
	{
		free(args->long_command);
		args->long_command = ft_strdup("");
		args->split_cmds = ft_split(args->long_command, 'a');
//		args->split_cmds[0] = ft_strdup(args->long_command);
	}
}
