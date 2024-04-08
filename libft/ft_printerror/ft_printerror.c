/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:55:37 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/24 19:04:53 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../includes/libft.h"

int	ft_printerror(const char *format, ...)
{
	va_list	args;
	int		count;
	int		ptr;

	ptr = 0;
	count = 0;
	va_start(args, format);
	count += ft_iterate_format_error(format, args, &ptr);
	if (ptr == -1)
	{
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (count);
}
