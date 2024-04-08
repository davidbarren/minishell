/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:54:36 by dbarrene          #+#    #+#             */
/*   Updated: 2023/11/15 13:05:09 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*t;
	int		b;
	int		e;

	if (!s1 || !set)
		return (NULL);
	b = 0;
	e = (int)(ft_strlen(s1) - 1);
	while (ft_strchr(set, s1[b]) && b <= e)
		b++;
	if (b > e)
		return (ft_strdup(&s1[e + 1]));
	while (ft_strchr(set, s1[e]) && e >= 0)
		e--;
	t = (char *)malloc(e - b + 2);
	if (!t)
		return (NULL);
	ft_strlcpy(t, &s1[b], e - b + 2);
	return (t);
}
