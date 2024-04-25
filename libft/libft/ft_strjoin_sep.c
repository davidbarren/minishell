/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:37:46 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/24 14:39:14 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin_sep(char *s1, char *s2, char sep)
{
	char	*joined;
	int		i;

	if (!s1 || !s2 || sep == '\0')
		return (NULL);
	i = 0;
	joined = malloc (ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!joined)
		return (NULL);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i++] = sep;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = 0;
	free (s1);
	return (joined);
}
