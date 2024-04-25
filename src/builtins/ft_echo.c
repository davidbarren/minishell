/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:25:49 by plang             #+#    #+#             */
/*   Updated: 2024/04/25 15:00:01 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_flag_validity(char *str)
{
	printf("%s\n", str);
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[0] != '-')
			return (1);
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_flags(char **words)
{
	int	i;
	i = 1;
	while (words[i] != '\0')
	{
		if (check_flag_validity(words[i]))
			break ;
		i++;
	}
	return (i);
}

void	ft_echo(char **words)
{
	int	i;
	int	flag_index;

	i = 0;
	flag_index = ft_check_flags(words);
	if (flag_index > 1)
	{
		printf("\n");
	}
	i += flag_index;
	while (words[i] != '\0')
	{
		printf("%s", words[i]);
		if (words[i + 1] != '\0')
			printf("%c", ' ');
		i++;
	}
	if (flag_index == 1)
	{
		printf("\n");
	}
}
