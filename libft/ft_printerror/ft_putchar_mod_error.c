/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_mod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:32:32 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/24 19:05:50 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putchar_mod_error(int c, int *ptr)
{
	int	count;

	if (*ptr == -1)
		return (-1);
	count = 0;
	if (write(2, &c, 1) == -1)
	{
		*ptr = -1;
		return (-1);
	}
	count++;
	return (count);
}
