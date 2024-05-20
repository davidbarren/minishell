/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:25:49 by plang             #+#    #+#             */
/*   Updated: 2024/05/18 15:23:57 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_echo_from_quotes(char **str)
{
	char	*copy;
	char	*start;
	int		i;
	char	c;
	
	i = 0;
	c = 0;
	copy = ft_strdup(*str);
	if (!copy)
		return ;
	start = copy;
	while (*copy)
	{
		// if (*copy == '"' || *copy == '\'')
		// {
		// 	c = *copy;
		// 	copy++;
		// 	while (*copy != c && *copy)
		// 	{
		// 		(*str)[i++] = *copy;
		// 		copy++;
		// 	}
		// 	c = 0;
		// }
		if (*copy != '"' && *copy != '\'' && c == 0)
			(*str)[i++] = *copy;
		copy++;
	}
	(*str)[i] = '\0';
	free(start);
}

void	ft_echo_clean(char **cmd_args)
{
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		clean_echo_from_quotes(&cmd_args[i]);
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
	// ft_echo_clean(words);
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

// if the argument in quiestion has more then one quote ' ", we clean it from the one that is a pair
