/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:09:04 by plang             #+#    #+#             */
/*   Updated: 2024/06/05 17:13:26 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_expand_quotes(char **str)
{
	t_clean	cq;

	ft_memset(&cq, 0, sizeof(cq));
	cq.copy = ft_strdup(*str);
	if (!cq.copy)
		return ;
	cq.start = cq.copy;
	while (cq.copy[cq.j])
	{
		if (cq.copy[cq.j] == '"' || cq.copy[cq.j] == '\'')
		{
			cq.c = cq.copy[cq.j];
			cq.j++;
			while (cq.copy[cq.j] != cq.c && cq.copy[cq.j])
			{
				(*str)[cq.i++] = cq.copy[cq.j];
				cq.j++;
			}
		}
		else if (cq.copy[cq.j] != '"' && cq.copy[cq.j] != '\'')
			(*str)[cq.i++] = cq.copy[cq.j];
		cq.j++;
	}
	(*str)[cq.i] = '\0';
	free(cq.start);
}

char	*expand_key(t_env *node)
{
	char	*key_value;

	key_value = ft_strdup(node->info);
	return (key_value);
}

void	get_len_for_key(char *arg, int *i, int *len)
{
	if (arg[*i] == '?')
	{
		(*len) += 1;
		(*i) += 1;
		return ;
	}
	while (arg[*i] != '\0' && ft_isalpha(arg[*i]))
	{
		(*len) += 1;
		(*i) += 1;
		if (arg[*i] == '_')
		{
			(*len) += 1;
			(*i) += 1;
		}
	}
}

void	expand_qm(char **check, char **rest, int es)
{
	free(*check);
	*check = ft_itoa(es);
	*check = ft_strjoin_flex(*check, *rest, 3);
	return ;
}

int	compare_against_envs(t_env **envs, char **check, char **rest)
{
	t_env	*temp;

	temp = *envs;
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->title, *check))
		{
			free(*check);
			*check = expand_key(temp);
			*check = ft_strjoin_flex(*check, *rest, 3);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
