/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:37:22 by plang             #+#    #+#             */
/*   Updated: 2024/05/08 17:29:13 by dbarrene         ###   ########.fr       */
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
	printf("Content of temp!:\n\n\n");
	printf("address of temp:%p\n", temp);
	printf("env_element of temp:%s\n", temp->env_element);
	printf("title of temp:%s\n", temp->title);
	printf("info of temp:%s\n", temp->info);

	unset = temp;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	printf("address of temp:%p\n", temp);
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
			if (!ft_strncmp(temp->env_element, cm_ar[i], ft_strlen(cm_ar[i])))
			{
				if (temp->prev == NULL)
					unset_first_node(env, temp);
				else
					unset_subsequent_node(temp);
				flag = 1;
				break ;
			}
			i++;
		}
		if (flag)
			break;
		temp = temp->next;
	}
	return (0);//EXIT_SUCCESS
}
