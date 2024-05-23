/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:32:53 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/24 01:34:12 by dbarrene         ###   ########.fr       */
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
