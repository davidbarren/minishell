/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:37:22 by plang             #+#    #+#             */
/*   Updated: 2024/06/25 17:25:41 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_first_node(t_env **env, t_env *temp)
{
	if (temp->next)
	{
		*env = temp->next;
		temp->next->prev = NULL;
	}
	else
		*env = NULL;
	if (temp->env_element)
	{
		free(temp->env_element);
		temp->env_element = NULL;
	}
	if (temp->info)
	{
		free(temp->info);
		temp->info = NULL;
	}
	if (temp->title)
	{
		free(temp->title);
		temp->title = NULL;
	}
	free(temp);
	temp = NULL;
}

void	unset_last_node(t_env *temp)
{
	t_env	*unset;

	unset = temp;
	temp->prev->next = NULL;
	if (unset->env_element)
		free(unset->env_element);
	if (unset->title)
		free(unset->title);
	if (unset->info)
		free(unset->info);
	if (unset)
		free(unset);
}

void	unset_subsequent_node(t_env *temp)
{
	t_env	*unset;

	unset = temp;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	if (unset->env_element)
		free(unset->env_element);
	if (unset->title)
		free(unset->title);
	if (unset->info)
		free(unset->info);
	if (unset)
		free(unset);
}

void	unset_key_found(t_env **env, t_env *temp, int *flag)
{
	if (temp->prev == NULL)
		unset_first_node(env, temp);
	else if (!temp->next)
		unset_last_node(temp);
	else
		unset_subsequent_node(temp);
	*flag = 1;
}

int	ft_unset(t_env **env, char **cm_ar)
{
	t_env	*temp;
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	while (cm_ar[i])
	{
		temp = *env;
		while (temp != NULL)
		{
			if (!ft_strcmp(temp->title, cm_ar[i]))
			{
				unset_key_found(env, temp, &flag);
				break ;
			}
			temp = temp->next;
		}
		i++;
	}
	return (0);
}
