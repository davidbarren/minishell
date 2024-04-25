/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:25:49 by plang             #+#    #+#             */
/*   Updated: 2024/04/23 19:33:36 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	ft_skip_space(char **s, char c)
{
	while (**s && **s == c)
	{
		(*s)++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

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
	printf("%d\n", flag_index);
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
		printf(" newline");
		printf("\n");
	}
}

int	main(int argc, char **argv)
{
	char	**array;
	int		i;

	(void)argc;
	i = 0;
	array = ft_split(argv[1], ' ');
	ft_echo(array);
	return (0);
}
