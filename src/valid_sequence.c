/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:44:26 by plang             #+#    #+#             */
/*   Updated: 2024/05/03 17:35:10 by plang            ###   ########.fr       */
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
		if (*str == a || *str == b)
		{
			str++;
			ft_skip_chars(&str, ' ');
			if (*str == c)
				return (1);
		}
		str++;
	}
	return (0);
}
