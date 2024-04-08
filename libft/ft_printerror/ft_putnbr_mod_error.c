/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:28:11 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/24 19:06:01 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr_mod_error(int n, int *ptr)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		if (ft_putstr_mod_error("-2147483648", ptr) == -1)
			return (*ptr = -1);
		else
			return (11);
	}
	else if (n < 0)
	{
		if (write(2, "-", 1) == -1)
			return (-1);
		n = -n;
		count += ft_putnbr_mod_error(n, ptr) + 1;
	}
	else if (n > 9)
	{
		count += ft_putnbr_mod_error(n / 10, ptr);
		count += ft_putnbr_mod_error(n % 10, ptr);
	}
	else
		count += ft_putchar_mod_error(n + 48, ptr);
	return (count);
}
