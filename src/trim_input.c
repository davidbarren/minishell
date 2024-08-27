/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:24:57 by plang             #+#    #+#             */
/*   Updated: 2024/06/25 17:26:38 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*trim_input(char *input, char c)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	j = 0;
	k = ft_strlen(input) - 1;
	if (input[i] == c)
		while (input[i] == c)
			i++;
	if (input[k] == c)
		while (input[k] == c)
			k--;
	str = malloc(((k - i + 1) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i <= k)
		str[j++] = input[i++];
	str[j] = '\0';
	free(input);
	return (str);
}
