/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:08:59 by plang             #+#    #+#             */
/*   Updated: 2024/06/05 17:13:24 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_not_sup_char(char *str, int *i, int *len, char *c)
{
	if (str[*i] == '$')
	{
		(*i) += 1;
		(*len) += 1;
	}
	if (str[*i] == '"' || str[*i] == '\'')
		*c = str[*i];
	(*i) += 1;
	(*len) += 1;
}

int	spacelen(char *str, int *i, int *len)
{
	while (str[*i] == ' ')
	{
		(*i) += 1;
		(*len) += 1;
	}
	return (*len);
}

int	get_part_len(char *str, int i)
{
	int		len;
	char	c;

	len = 0;
	c = 0;
	if (str[i] == ' ')
		return (spacelen(str, &i, &len));
	if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
	{
		i++;
		return (1);
	}
	if (!ft_isalnum(str[i]) && str[i] != 0)
		set_not_sup_char(str, &i, &len, &c);
	while (str[i] != '\0')
	{
		if (!c && !ft_isalnum(str[i]) && str[i] != '_' && str[i] != '?')
			return (len);
		if (c && str[i] == c)
			return (len + 1);
		i++;
		len++;
	}
	return (len);
}

char	*is_expansion_valid(t_env **envs, char *arg, int i, int es)
{
	char	*check;
	int		lenstart[2];
	char	*rest;

	lenstart[0] = 0;
	lenstart[1] = i;
	get_len_for_key(arg, &i, &lenstart[0]);
	check = ft_substr(arg, lenstart[1], lenstart[0]);
	rest = ft_substr(arg, i, (ft_strlen(arg) - i));
	if (check[0] == '?')
	{
		expand_qm(&check, &rest, es);
		return (check);
	}
	if (compare_against_envs(envs, &check, &rest))
		return (check);
	free(check);
	check = rest;
	return (check);
}

int	get_qflag(char *arg)
{
	int	flag;
	int	j;

	j = 0;
	flag = 0;
	while (arg[j] != '\0')
	{
		if (arg[j] == '\'')
		{
			flag = 2;
			break ;
		}
		else if (arg[j] == '"')
		{
			flag = 1;
			break ;
		}
		j++;
	}
	return (flag);
}
