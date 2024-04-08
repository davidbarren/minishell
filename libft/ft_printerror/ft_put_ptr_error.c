/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:02:12 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/24 19:05:34 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_put_ptr_error(unsigned long n, int *ptr)
{
	int	count;

	if (*ptr == -1)
		return (-1);
	count = 0;
	count += ft_putstr_mod_error("0x", ptr);
	count += ft_put_hex_error(n, 0, ptr);
	return (count);
}
