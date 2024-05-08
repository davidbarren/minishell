/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:27:49 by plang             #+#    #+#             */
/*   Updated: 2024/05/07 12:04:00 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_syntax_check(char	*line)
{
	if (valid_quotes(line)
		|| valid_redirect(line)
		|| valid_pipes(line)
		|| valid_chars(line)
		|| valid_sequence(line, '<', '>', '|'))
		return (1);
	return (0);
}


//work on this with the printing of the correct message and add all the changes from the work_minishell
