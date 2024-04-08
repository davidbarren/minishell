/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:53:54 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/24 19:05:39 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_put_unsigned_error(unsigned int n, int *ptr)
{
	unsigned int	count;

	count = 0;
	if (n > 9)
	{
		count += ft_put_unsigned_error(n / 10, ptr);
		count += ft_put_unsigned_error(n % 10, ptr);
	}
	else
		count += ft_putchar_mod_error(n + 48, ptr);
	return (count);
}
