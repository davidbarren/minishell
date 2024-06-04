/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:32:53 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/03 18:01:06 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	baboon_free(char **stackarr)
{
	int	i;

	i = 0;
	if (stackarr)
		while (stackarr[i])
			free(stackarr[i++]);
}

int	cmd_is_echo(char *str)
{
	if (ft_strcmp_up_lo(str, "echo"))
		return (0);
	return (1);
}

int	ft_emptyline(char *line)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		else 
			i++;
	}
	return (1);
}
