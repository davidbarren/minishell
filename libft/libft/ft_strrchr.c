/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:56:06 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/16 15:03:21 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	d;
	int		i;
	char	*ptr;

	ptr = NULL;
	i = ft_strlen(s);
	d = (char)c;
	if (c == 0)
	{
		ptr = (char *)&s[i];
		return (ptr);
	}
	while (i >= 0)
	{
		if (s[i] == d)
		{
			ptr = (char *)&s[i];
			return (ptr);
		}
		i--;
	}
	return (ptr);
}
