/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:11 by plang             #+#    #+#             */
/*   Updated: 2024/04/25 14:58:35 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_pipes(char *str)
{
	int	check;

	check = 0;
	ft_skip_char(&str, ' ');
	if (*str == '|')
		check = 1;
	while (*str != '\0')
	{
		if (*str == '|')
		{
			str++;
			ft_skip_char(&str, ' ');
			if (*str == '\0' || *str == '|')
			{
				check = 1;
				break ;
			}
		}
		str++;
	}
	return (check);
}
