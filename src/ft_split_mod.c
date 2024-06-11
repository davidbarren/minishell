/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:17:42 by plang             #+#    #+#             */
/*   Updated: 2024/06/04 15:24:12 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_free(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	return (0);
}

void	ft_get_start(char **s, char c)
{
	while (**s && **s == c)
	{
		(*s)++;
	}
}

int	get_str_len(char *str, t_split_m *variables, int x)
{
	variables->i = 0;
	while (str[x] != '\0')
	{
		if (str[x] == ' ')
			break ;
		if ((str[x] == '"' || str[x] == '\'')
			&& (quote_count(str, str[x]) % 2 == 0))
		{
			variables->temp = str[x];
			x++;
			variables->i++;
			while (str[x] != variables->temp && str[x])
			{
				x++;
				variables->i++;
			}
		}
		if (str[x])
		{
			x++;
			variables->i++;
		}
	}
	return (variables->i);
}

int	get_str_count(char *str)
{
	int		count;
	char	temp;

	count = 0;
	temp = 0;
	while (*str != '\0')
	{
		if (*str != ' ')
			count++;
		while (*str != ' ' && *str)
		{
			if ((*str == '"' || *str == '\'')
				&& (quote_count(str, *str) % 2 == 0))
			{
				temp = *str;
				str++;
				while (*str != temp && *str && (*str))
					str++;
			}
			if (*str + 1)
				str++;
		}
		ft_get_start(&str, ' ');
	}
	return (count);
}

char	**ft_split_mod(char *str, char c)
{
	t_split_m	t_d;

	ft_memset(&t_d, 0, sizeof(t_d));
	t_d.str_cnt = get_str_count(str);
	t_d.array = malloc((t_d.str_cnt + 1) * sizeof(char *));
	if (!t_d.array)
		return (NULL);
	while (t_d.str_cnt > t_d.ar_i)
	{
		ft_get_start(&str, c);
		t_d.str_len = get_str_len(str, &t_d, 0);
		t_d.array[t_d.ar_i] = ft_substr(str, 0, t_d.str_len);
		if (!t_d.array[t_d.ar_i])
			return (ft_free(t_d.array));
		str += t_d.str_len;
		t_d.ar_i++;
	}
	t_d.array[t_d.ar_i] = 0;
	return (t_d.array);
}
