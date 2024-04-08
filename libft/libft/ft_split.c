/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:04:01 by dbarrene          #+#    #+#             */
/*   Updated: 2024/03/23 13:15:44 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_skip_delims(const char **s, char c)
{
	while (**s && **s == c)
		(*s)++;
}

static size_t	ft_strchr_count(const char *s, char c)
{
	size_t		count;

	if (!*s)
		return (0);
	count = 1;
	while (*s)
	{
		if (*s == c)
		{
			ft_skip_delims(&s, c);
			if (*s)
				count++;
		}
		else
			s++;
	}
	return (count);
}

static char	**ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**strarr;
	size_t	j;
	size_t	i;

	if (!s)
		return (NULL);
	ft_skip_delims(&s, c);
	strarr = ft_calloc((1 + ft_strchr_count(s, c)), sizeof(char *));
	if (!strarr)
		return (0);
	i = 0;
	while (*s)
	{
		j = 0;
		while (s[j] && s[j] != c)
			j++;
		strarr[i] = ft_substr(s, 0, j);
		if (!strarr[i++])
			return (ft_free(strarr));
		s += j;
		ft_skip_delims(&s, c);
	}
	return (strarr);
}
