/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:11 by plang             #+#    #+#             */
/*   Updated: 2024/05/24 17:00:52 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	ft_skip_quotes(char **str)
// {
// 	char	c;

// 	c = **str;
// 	(*str)++;
// 	while (**str && **str != c)
// 	{
// 		(*str)++;
// 	}
// }

void	skipping_through_quotes(char *str, int *i)
{
	char	temp;

	temp = 0;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		temp = str[*i];
		*i += 1;
		while (str[*i] != temp && str[*i] != '\0')
			*i += 1;
	}
}

int	valid_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (3);
	// ft_skip_chars(&str, ' ');
	// if (*str == '|')
	// 	return (3);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			skipping_through_quotes(str, &i);
			//ft_skip_quotes(&str);
		}
		if (str[i] == '|')
		{
			i++;
			// ft_skip_chars(&str, ' ');
			// if (*str == '\0' || *str == '|')
			// 	return (3);
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (3);
		}
		i++;
		//str++;
	}
	return (0);
}
