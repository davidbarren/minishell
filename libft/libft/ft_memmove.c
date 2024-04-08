/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:24:41 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/15 13:01:42 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*source;
	unsigned char	*dest;

	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (source > dest)
		ft_memcpy(dst, src, len);
	i = (len - 1);
	if (source < dest)
	{
		while (len > 0)
		{
			dest[i] = source[i];
			i--;
			len--;
		}
	}
	return (dst);
}
