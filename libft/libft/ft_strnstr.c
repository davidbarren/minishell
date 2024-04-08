/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:47:39 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/15 13:04:43 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = (char *)haystack;
	i = 0;
	j = 0;
	if ((ft_strlen(needle) == 0) || (haystack == 0 && len == 0))
		return (ptr);
	while ((haystack[i] != 0) && (i < len))
	{
		while (haystack[i + j] == needle[j] && (j < (len - i)))
		{
			j++;
			if (needle[j] == 0)
			{
				ptr = (char *)&haystack[i];
				return (ptr);
			}
		}
		i++;
		j = 0;
	}
	return (NULL);
}
