/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:25 by plang             #+#    #+#             */
/*   Updated: 2024/05/10 14:38:39 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_next_quote(char *str, int *i, int *dq, int *sq)
{
	char	c;

	c = str[*i];
	while (str[*i] != '\0')
	{
		if (str[*i] == '"')
		{
			*dq += 1;
		}
		if (str[*i + 1] == '"')
		{
			*dq += 1;
		}
		if (str[*i] == '\'')
		{
			*sq += 1;
		}
		if (str[*i + 1] == '\'')
		{
			*sq += 1;
		}
		*i += 1;
		if (str[*i] == c)
			return ;
	}
}

int	quote_count(char *str, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			k++;
		i++;
	}
	return (k);
}

int	valid_quotes(char *str)
{
	int		i;
	int		squotes;
	int		dquotes;
	char	type;

	i = 0;
	squotes = 0;
	dquotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			type = str[i];
			find_next_quote(str, &i, &dquotes, &squotes);
			if (type == '"' && dquotes % 2 != 0)
				return (1);
			if (type == '\'' && squotes % 2 != 0)
				return (1);
		}
		if (str[i] != '\0')
			i++;
	}
	return (0);
}
