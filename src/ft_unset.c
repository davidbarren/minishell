/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:37:22 by plang             #+#    #+#             */
/*   Updated: 2024/05/07 11:34:12 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_first_node(t_env **env, t_env *temp)
{
	t_env	*unset;
	
	*env = temp->next;
	temp->next->prev = NULL;
	unset = temp;
	free(unset->env_element);
	free(unset->title);
	free(unset->info);
	free(unset);
}

void	unset_subsequent_node(t_env *temp)
{
	t_env	*unset;
	
	unset = temp;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(unset->env_element);
	free(unset->title);
	free(unset->info);
	free(unset);
}

int	ft_unset(t_env **env, char **cm_ar)
{
	t_env	*temp;
	int		i;

	temp = *env;
	while (temp != NULL)
	{
		i = 1;
		while (cm_ar[i])
		{
			if (!ft_strncmp(temp->env_element, cm_ar[i], ft_strlen(cm_ar[i])))
			{
				if (temp->prev == NULL)
					unset_first_node(env, temp);
				else
					unset_subsequent_node(temp);
				break ;
			}
			i++;
		}
		temp = temp->next;
	}
	return (0);//EXIT_SUCCESS
}
