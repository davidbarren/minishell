/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:09:25 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/04 20:09:47 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_skip_delims(const char **s, char c)
{
	while (**s && **s == c)
		(*s)++;
}

static int	word_count(const char *s, char c, t_wordc *wordc)
{
	if (!*s)
		return (0);
	wordc->i = 1;
	while (*s)
	{
		if ((*s == '\'' || *s == '\"') && (*s + 1))
		{
			wordc->flag = 1;
			wordc->temp = *s;
			s++;
			while (*s != wordc->temp)
				s++;
			wordc->flag = 0;
		}
		if (*s == c && !wordc->flag)
		{
			ft_skip_delims(&s, c);
			if (*s)
				wordc->i++;
		}
		else
			s++;
	}
	return (wordc->i);
}

int	ft_quotelen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
/*
char **ft_newsplit(const char *s, char c)
{
	int		i;
	int		j;
	char	**array;
	char	temp;

	if (!s)
		return (NULL);
	i = 0;
	array = ft_calloc(1 + word_count(s,c), sizeof (char *));
	if (!array)
		return (NULL);
	printf("Wordcount: %d\n", word_count(s, c));
	ft_skip_delims(&s, c);
	while (*s)
	{
		j = 0;
			while (s[j] != c && str[j] && (str[j] != '\'' && str[j] != '\"'))
				j++;
		if (s[j] == '\'' || str[j] == '\"')
		{
			temp = s[j];
//			ft_skip_delims(&s, temp);
//			 ft_skip_delims(&s, c);
//			 s+= 1;
			printf("Temp char: %c\n", temp);
			j+= ft_quotelen(s + j + 1,  temp);
			while (s[j] && str[j] != c)
				j++;
			array[i++] = ft_subs(str, 0, j);
			if (!array)
				free_2d(array);
			s += j;
			 ft_skip_delims(&s, c);
		}
		else
		{
			array[i++] = ft_subs(str, 0, j);
			if (!array)
				free_2d(array);
			s += j;
			ft_skip_delims(&s, c);
		}
	}
	array[i] = NULL;
	return (array);
}
*/

void	ft_splitmaker(const char *s, char c, t_qsplit *p)
{
	while (*s)
	{
		p->j = 0;
		while (s[p->j] != c && s[p->j] && (s[p->j] != '\'' && s[p->j] != '\"'))
			p->j++;
		if (s[p->j] == '\'' || s[p->j] == '\"')
		{
			p->temp = s[p->j];
			p->j += ft_quotelen((s + p->j + 1), p->temp);
			while (s[p->j] && s[p->j] != c)
				p->j++;
			p->arr[p->i++] = ft_substr(s, 0, p->j);
			if (!p->arr)
				free_2d(p->arr);
		}
		else
		{
			p->arr[p->i++] = ft_substr(s, 0, p->j);
			if (!p->arr)
				free_2d(p->arr);
		}
		s += p->j;
		ft_skip_delims(&s, c);
	}
}

char	**ft_quotesplit(const char *s, char c)
{
	t_qsplit	splitter;
	t_wordc		wordc;

	ft_bzero(&splitter, sizeof(t_qsplit));
	ft_bzero(&wordc, sizeof(t_wordc));
	if (!s)
		return (NULL);
	splitter.arr = ft_calloc(1 + word_count(s, c, &wordc), sizeof(char *));
	if (!splitter.arr)
		return (NULL);
	ft_skip_delims(&s, c);
	ft_splitmaker(s, c, &splitter);
	splitter.arr[splitter.i] = NULL;
	return (splitter.arr);
}
