/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:25:49 by plang             #+#    #+#             */
/*   Updated: 2024/06/06 19:22:00 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_clean(char **cmd_args)
{
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		clean_expand_quotes(&cmd_args[i]);
		i++;
	}
}

int	check_flag_validity(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
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
	ft_echo_clean(words);
	flag_index = ft_check_flags(words);
	i = flag_index;
	while (words[i] != 0)
	{
		ft_printf("%s", words[i]);
		if (words[i + 1] != 0)
			ft_printf("%c", ' ');
		i++;
	}
	if (flag_index == 1)
		ft_printf("\n");
	return (0);
}
