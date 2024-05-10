/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:11 by plang             #+#    #+#             */
/*   Updated: 2024/05/10 14:38:09 by plang            ###   ########.fr       */
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

int	valid_pipes(char *str)
{
	ft_skip_chars(&str, ' ');
	if (*str == '|')
		return (3);
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
			ft_skip_quotes(&str);
		if (*str == '|')
		{
			str++;
			ft_skip_chars(&str, ' ');
			if (*str == '\0' || *str == '|')
				return (3);
		}
		str++;
	}
	return (0);
}
