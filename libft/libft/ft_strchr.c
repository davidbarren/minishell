/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:26:15 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/16 15:03:15 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	d;
	int		i;
	char	*ptr;

	i = 0;
	d = (char)c;
	ptr = NULL;
	while (s[i] != 0)
	{
		if (s[i] == d)
		{
			ptr = (char *)&s[i];
			return (ptr);
		}
		i++;
	}
	if (d == '\0')
		ptr = (char *)&s[ft_strlen(s)];
	return (ptr);
}
