/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:06:11 by plang             #+#    #+#             */
/*   Updated: 2024/05/28 19:23:13 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skipping_through_quotes(char *str, int *i)
{
	char	temp;

	temp = 0;
	if ((str[*i] == '"' || str[*i] == '\'') && str[*i + 1] != '\0')
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
	// while (str[i] == ' ' && str[i])
	// 	i++;
	ft_skip_chars(&str, ' ');
	if (str[i] == '|')
		return (3);
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i + 1] != '\0')
			i++;
		if (str[i] == '"' || str[i] == '\'')
			skipping_through_quotes(str, &i);
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (3);
		if (str[i] == '"' || str[i] == '\'')
			skipping_through_quotes(str, &i);
		}
		i++;
	}
	return (0);
}
