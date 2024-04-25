/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:42:20 by plang             #+#    #+#             */
/*   Updated: 2024/04/19 16:12:03 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h> // remove

int	not_supported_chars(char *str, char c)
{
	int		i;
	int		flag;
	char	temp;

	i = 0;
	flag = 0;
	temp = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'') && flag == 0)
		{
			flag = 1;
			temp = str[i];
			i++;
			while (str[i] != temp && str[i] != '\0')
				i++;
			flag = 0;
		}
		if ((flag == 0 && str[i] == c)
			|| (flag == 0 && str[i] == c && str[i + 1] == c))
			return (1);
		i++;
	}
	return (0);
}

int	first_or_last(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (str[i] == ' ')
		i++;
	j--;
	while (str[j] == ' ')
		j--;
	if (str[i] == c || str[j] == c)
		return (1);
	return (0);
}

int	valid_chars(char *str)
{
	if (first_or_last(str, '&'))
		return (1);
	if (first_or_last(str, ';'))
		return (1);
	if (first_or_last(str, '!'))
		return (1);
	if (not_supported_chars(str, '&'))
		return (1);
	if (not_supported_chars(str, '!'))
		return (1);
	if (not_supported_chars(str, ';'))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	int	check;

	check = valid_chars(argv[1]);
	printf("check: %d\n", check);
	return (0);
}
