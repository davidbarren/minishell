/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:05:03 by dbarrene          #+#    #+#             */
/*   Updated: 2024/03/24 15:14:07 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	l;

	if (!s)
		return ((char *)ft_calloc(1, 1));
	l = ft_strlen(s);
	if (start > l)
		return ((char *)ft_calloc(1, 1));
	i = 0;
	l = ft_strlen(s + start);
	if (l > len)
		l = len;
	sub = malloc (l + 1);
	if (!sub)
		return (NULL);
	while (i < len && s[i + start] != 0)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}
