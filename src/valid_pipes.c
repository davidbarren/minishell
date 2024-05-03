/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:11 by plang             #+#    #+#             */
/*   Updated: 2024/05/03 14:14:15 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_skip_quotes(char **str)
{
	char	c;

	c = **str;
	(*str)++;
	while (**str && **str != c)
	{
		(*str)++;
	}
}

int	valid_pipes(char *str)
{
	ft_skip_chars(&str, ' ');
	if (*str == '|')
		return (1);
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
			ft_skip_quotes(&str);
		if (*str == '|')
		{
			str++;
			ft_skip_chars(&str, ' ');
			if (*str == '\0' || *str == '|')
				return (1);
		}
		str++;
	}
	return (0);
}

// int	valid_pipes(char *str)
// {
// 	int	check;

// 	check = 0;
// 	ft_skip_chars(&str, ' ');
// 	if (*str == '|')
// 		check = 1;
// 	while (*str != '\0')
// 	{
// 		if (*str == '|')
// 		{
// 			str++;
// 			ft_skip_chars(&str, ' ');
// 			if (*str == '\0' || *str == '|')
// 			{
// 				check = 1;
// 				break ;
// 			}
// 		}
// 		str++;
// 	}
// 	return (check);
// }
