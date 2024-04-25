/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:11 by plang             #+#    #+#             */
/*   Updated: 2024/04/19 12:01:06 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	ft_skip_space(char **str, char c)
// {
// 	while (**str && **str == c)
// 	{
// 		(*str)++;
// 	}
// }

#include "libft.h"

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

#include <stdio.h>

int	main(int argc, char **argv)
{
	(void)argc;
	int	check;

	check = valid_pipes(argv[1]);
	printf("%d\n", check);
	return (0);
}
