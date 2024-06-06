/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:27:49 by plang             #+#    #+#             */
/*   Updated: 2024/06/06 20:36:58 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_syntax_check(char	*line)
{
	int	error;

	error = valid_quotes(line);
	if (error)
		return (error);
	error = valid_redirect(line);
	if (error)
		return (error);
	error = valid_pipes(line);
	if (error)
		return (error);
	error = valid_chars(line);
	if (error)
		return (error);
	error = valid_chars2(line);
	if (error)
		return (error);
	error = valid_sequence(line, '<', '>', '|');
	if (error)
		return (error);
	return (0);
}

int	syntax_validation(char *str)
{
	int	check;

	if (!*str)
		return (-1);
	check = valid_syntax_check(str);
	if (check > 0)
	{
		if (check == 1)
			ft_putstr_fd("🐒: syntax error, open quotes\n", 2);
		if (check == 2)
			ft_putstr_fd("🐒: syntax error near unexpected token `nl'\n", 2);
		if (check == 3)
			ft_putstr_fd("🐒: syntax error near unexpected token `|'\n", 2);
		if (check == 5)
			ft_putstr_fd("🐒: syntax error, forbidden sequence\n", 2);
		if (check == 6)
			ft_putstr_fd("🐒: syntax error near unexpected token `<'\n", 2);
		check = 258;
	}
	return (check);
}
