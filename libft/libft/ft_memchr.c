/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:55:57 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/16 15:03:06 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	d;
	unsigned char	*arr;
	void			*ptr;

	d = (unsigned char)c;
	arr = (unsigned char *)s;
	ptr = 0;
	i = 0;
	while (i < n)
	{
		if (arr[i] == d)
		{
			ptr = &arr[i];
			return (ptr);
		}
		i++;
	}
	return (ptr);
}
