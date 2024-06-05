/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:16:59 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/05 18:18:58 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	input_valid_routine(t_input *input, char *line)
{
	prep_input(line, input);
	free_structs(input->arg_struct, input->pipe_count);
}
