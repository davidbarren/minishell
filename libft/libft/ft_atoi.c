/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:31:50 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/16 18:57:06 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int				n;
	unsigned long	r;

	n = 1;
	r = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			n = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		if ((r > LMAX / 10) || (r == LMAX / 10 && *str < '8'))
		{
			if (n == 1)
				return ((int) 9223372036854775807);
			return ((int) -9223372036854775807 - 1);
		}
		r = r * 10 + *str - '0';
		str++;
	}
	return ((int)(r * n));
}
