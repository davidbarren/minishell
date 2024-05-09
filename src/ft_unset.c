/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:37:22 by plang             #+#    #+#             */
/*   Updated: 2024/05/09 17:52:25 by dbarrene         ###   ########.fr       */
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

int	ft_unset(t_env **env, char **cm_ar)
{
	t_env	*temp;
	int		i;
	int		flag;

	flag = 0;
	temp = *env;
	while (temp != NULL)
	{
		i = 1;
		while (cm_ar[i])
		{
			if (!ft_strncmp(temp->title, cm_ar[i], ft_strlen(cm_ar[i])))
			{
				if (temp->prev == NULL)
					unset_first_node(env, temp);
				else if (!temp->next)
					unset_last_node(temp);
				else
					unset_subsequent_node(temp);
				flag = 1;
				break ;
			}
			i++;
		}
		if (flag)
			break ;
		temp = temp->next;
	}
	return (0);//EXIT_SUCCESS
}
