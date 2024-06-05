/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:44:26 by plang             #+#    #+#             */
/*   Updated: 2024/06/05 10:40:18 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_skip_quotes(char **str)
{
	char	c;

	c = **str;
	(*str)++;
	while (**str && **str != c)
	{
		(*str)++;
	}
}

int	valid_sequence(char *str, char a, char b, char c)
{
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
			ft_skip_quotes(&str);
		if (!*str)
			break ;
		if (*str == a || *str == b)
		{
			str++;
			ft_skip_chars(&str, ' ');
			if (*str == c)
				return (5);
		}
		str++;
	}
	return (0);
}
