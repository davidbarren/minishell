/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterate_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:19:01 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/28 18:18:49 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_iterate_format_error(const char *format, va_list args, int *ptr)
{
	int	count;
	int	temp;

	count = 0;
	temp = 0;
	while (*format != 0)
	{
		if (*format == '%')
		{
			temp = ft_format_check_error(*++format, args, ptr);
			if (temp == -1)
				return (-1);
			count += temp;
			format++;
		}
		else if (*format != '%' && *format != 0)
		{
			temp = ft_putchar_mod_error(*format, ptr);
			if (temp == -1)
				return (-1);
			count += temp;
			format++;
		}
	}
	return (count);
}
