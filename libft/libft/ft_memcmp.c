/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:06:33 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/16 15:02:57 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1)
	{
		if (p1[i] == p2[i])
			i++;
		else
			break ;
	}
	return (p1[i] - p2[i]);
}
/*
int	main(void)
{
	char str1[] = "\xff\xaa\xde\x12";
	char str2[] = "\xff\xaa\xde\x12MACOSAAAAA";
	printf("%i\n", ft_memcmp(str1, str2, 4));
	printf("%i\n", memcmp(str1, str2, 4));
	return (0);
}*/
