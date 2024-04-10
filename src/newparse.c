/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/09 18:00:55 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenize_input(t_args *args, char *input)
{
	int i = 0;
	t_split splitter;
	char *stringi;
	args->arglist = split_quotes(input,' ', '\"', &splitter);
	while (args->arglist[i])
		ft_printf("%s\n", args->arglist[i++]);
	stringi = remove_whitespace(input);
//	printf("Stringi: %s\n", stringi);
}

char *remove_whitespace(char *str)
{
	int len;
	int spacecount;
	char *fullstr;
	int i;
	int k;

	k = 0;
	i = 0;
	len = ft_strlen(str);
	spacecount = count_spaces(str);
	fullstr = malloc (sizeof (char) * len - spacecount + 1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
		{
			fullstr[k] = str[i];
			k++;
			i++;
		}
		else
			i++;
	}
	fullstr[k] = '\0';
	return (fullstr);
}


int	count_spaces(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == ' ')
			count++;
		str++;
	}
	return (count);
}
