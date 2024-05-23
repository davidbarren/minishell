/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:02:40 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/21 17:35:28 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	skip_delims(const char **str, char c)
{
	while (**str && **str == c)
		(*str)++;
}

static int	count_words(const char *str, char c, char q)
{
	int	count;

	if (!str || !*str)
		return (0);
	count = 1;
	while (*str)
	{
		if (*str == c)
		{
			skip_delims(&str, c);
			if ((*str == q) || (*str == '\''))
			{
				count++;
				str++;
				while (*str != q && *str != '\'')
					str++;
			}
			else if (*str)
				count++;
		}
		else
			str++;
	}
	return (count);
}

static void	split_free(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
	return ;
}

static void	ft_split_quotes(const char	*str, char delim, char q, t_split *st)
{
	skip_delims(&str, delim);
	while (*str && st->wc > st->i)
	{
		st->j = 0;
		if (*str != q && *str != '\'')
			skip_delims(&str, delim);
		if (str[st->j] == q || str[st->j] == '\'')
		{
			st->j++;
			while (str[st->j] != q && str[st->j] != '\'')
				st->j++;
			st->j++;
			st->split_arr[st->i++] = ft_substr(str, 1, ((st->j) - 2));
			str += st->j;
		}
		st->j = 0;
		skip_delims(&str, delim);
		while (str[st->j] && str[st->j] != delim)
			st->j++;
		st->split_arr[st->i] = ft_substr(str, 0, st->j);
		if (!st->split_arr[st->i++])
			(split_free(st->split_arr));
		str += st->j;
	}
}

char	**split_quotes(const char *str, char delim, char q, t_split *st)
{
	if (!*str || !str)
		return (NULL);
	st->wc = count_words(str, delim, q);
	st->split_arr = ft_calloc(st->wc + 1, sizeof (char *));
	if (!st->split_arr)
		return (NULL);
	st->i = 0;
	ft_split_quotes(str, delim, q, st);
	st->split_arr[st->wc] = NULL;
	return (st->split_arr);
}
