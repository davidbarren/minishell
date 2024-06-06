/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoteclean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:18:51 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/06 19:19:45 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_expand_quotes(char **str)
{
	t_clean	cq;

	ft_memset(&cq, 0, sizeof(cq));
	cq.copy = ft_strdup(*str);
	if (!cq.copy)
		return ;
	cq.start = cq.copy;
	while (cq.copy[cq.j])
	{
		if (cq.copy[cq.j] == '"' || cq.copy[cq.j] == '\'')
		{
			cq.c = cq.copy[cq.j];
			cq.j++;
			while (cq.copy[cq.j] != cq.c && cq.copy[cq.j])
			{
				(*str)[cq.i++] = cq.copy[cq.j];
				cq.j++;
			}
		}
		else if (cq.copy[cq.j] != '"' && cq.copy[cq.j] != '\'')
			(*str)[cq.i++] = cq.copy[cq.j];
		cq.j++;
	}
	(*str)[cq.i] = '\0';
	free(cq.start);
}
