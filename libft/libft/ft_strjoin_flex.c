/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_flex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:45:45 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/28 12:08:48 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <strings.h>

static void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_strjoin_flex(const char *s1, const char *s2, int flag)
{
	char	*joined;
	int		len1;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	joined = malloc(len1 + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strcpy(joined + len1, s2);
	if (flag == 1)
		free((char *)s1);
	if (flag == 2)
		free((char *)s2);
	if (flag == 3)
	{
		free((char *)s2);
		free((char *)s1);
	}
	return (joined);
}
