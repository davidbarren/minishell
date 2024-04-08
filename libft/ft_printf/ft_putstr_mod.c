/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:32:06 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/24 19:06:11 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr_mod(char *s, int *ptr)
{
	int	count;

	if (*ptr == -1)
		return (-1);
	count = 0;
	if (!s)
		return (ft_putstr_mod("(null)", ptr));
	while (*s != 0)
	{
		if (ft_putchar_mod(*s++, ptr) == -1)
		{
			*ptr = -1;
			return (-1);
		}
		count++;
	}
	return (count);
}
