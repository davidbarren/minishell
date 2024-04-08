/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:09:55 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/15 13:18:39 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_numlen(int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n == 2147483647)
		return (10);
	while (n < 0)
	{
		l++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

static int	ft_check_negative(char *str, int n)
{
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		temp;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_numlen(n);
	i = len - 1;
	str = malloc((len + 1) * sizeof (char));
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[i] = n + '0';
	n = ft_check_negative(str, n);
	while (n > 0)
	{
		temp = n % 10;
		str[i] = temp + '0';
		i--;
		n = n / 10;
	}
	str[len] = 0;
	return (str);
}
