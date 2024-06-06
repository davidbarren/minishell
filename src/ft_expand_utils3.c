/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:09:04 by plang             #+#    #+#             */
/*   Updated: 2024/06/06 19:20:15 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	expand_rest(t_env **envs, char **arg, int *i, int es)
{
	while ((*arg)[*i] != '\0')
	{
		if ((*arg)[*i] == '$')
		{
			expand_check_arguments(envs, arg, es);
		}
		(*i) += 1;
	}
}
