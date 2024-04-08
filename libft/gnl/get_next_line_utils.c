/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:25:47 by dbarrene          #+#    #+#             */
/*   Updated: 2023/12/16 11:55:18 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strlen_mod(char *str, char c)
{
	int	i;

	if (!str || str[0] == 0)
		return (0);
	i = 0;
	while ((str[i] != c) && (str[i]))
		i++;
	return (i);
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != 0)
// 		i++;
// 	return (i);
// }

char	*ft_substr_mod(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	l;

	sub = NULL;
	l = ft_strlen(s);
	if (start > l)
		return (NULL);
	i = 0;
	l = ft_strlen(s + start);
	if (l > len)
		l = len;
	sub = malloc (l + 1);
	if (!sub)
		return (NULL);
	while (i < len && s[i + start] != 0)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}

char	*ft_strchr_mod(const char *s, int c)
{
	char	d;
	int		i;
	char	*ptr;

	i = 0;
	d = (char)c;
	ptr = NULL;
	if (!s)
		return (NULL);
	while (s[i] != 0)
	{
		if (s[i] == d)
		{
			ptr = (char *)&s[i];
			return (ptr);
		}
		i++;
	}
	if (d == '\0')
		ptr = (char *)&s[ft_strlen(s)];
	return (ptr);
}

// char	*ft_strdup(const char *s)
// {
// 	char	*dup;
// 	int		i;

// 	i = 0;
// 	dup = (char *)malloc (1 + ft_strlen(s) * sizeof (char));
// 	if (dup == NULL)
// 		return (0);
// 	while (s[i] != 0)
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = 0;
// 	return (dup);
// }
