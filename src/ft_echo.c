/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:25:49 by plang             #+#    #+#             */
/*   Updated: 2024/05/09 17:54:55 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_flag_validity(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '\0')
		return (1);
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
	while (words[i])
	{
		if (check_flag_validity(words[i]))
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(char **words)
{
	int	i;
	int	flag_index;

	i = 0;
	flag_index = ft_check_flags(words);
	i = flag_index;
	while (words[i] != 0)
	{
		printf("%s", words[i]);
		if (words[i + 1] != 0)
			printf("%c", ' ');
		i++;
	}
	if (flag_index == 1)
		printf("\n");
	return (0); //EXIT_SUCCESS
}
