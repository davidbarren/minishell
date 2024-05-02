/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:27:49 by plang             #+#    #+#             */
/*   Updated: 2024/04/30 13:32:39 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_syntax_check(char	*line)
{
	if (valid_quotes(line) && (valid_redirect(line)
			|| valid_pipes(line)
			|| valid_chars(line)))
		return (1);
	return (0);
}
