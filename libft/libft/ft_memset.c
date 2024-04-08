/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:23:37 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/15 13:01:52 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	d;
	unsigned char	*b;

	i = 0;
	d = (unsigned char)c;
	b = (unsigned char *)str;
	while (i < len)
	{
		b[i] = d;
		i++;
	}
	return (b);
}
