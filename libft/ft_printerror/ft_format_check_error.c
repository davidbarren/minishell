/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:34:34 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/28 18:24:35 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_format_check_error(char spec, va_list args, int *ptr)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += ft_putchar_mod_error(va_arg(args, int), ptr);
	else if (spec == 's')
		count += ft_putstr_mod_error(va_arg(args, char *), ptr);
	else if (spec == 'd' || spec == 'i')
		count += ft_putnbr_mod_error(va_arg(args, int), ptr);
	else if (spec == 'u')
		count += ft_put_unsigned_error(va_arg(args, unsigned int), ptr);
	else if (spec == 'p')
		count += ft_put_ptr_error(va_arg(args, unsigned long), ptr);
	else if (spec == 'x')
		count += ft_put_hex_error(va_arg(args, unsigned int), 0, ptr);
	else if (spec == 'X')
		count += ft_put_hex_error(va_arg(args, unsigned int), 1, ptr);
	else if (spec == '%')
		count += ft_putchar_mod_error('%', ptr);
	else
		count += ft_putchar_mod_error(spec, ptr);
	if (count == -1)
		return (-1);
	return (count);
}
