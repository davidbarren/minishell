/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:37:22 by plang             #+#    #+#             */
/*   Updated: 2024/04/28 16:35:10 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_env **env, char **cmd_args)
{
	t_env	*temp;
	t_env	*unset;
	int		i;

	temp = *env;
	while (temp != NULL)
	{
		i = 1;
		while (cmd_args[i])
		{
			if (!ft_strncmp(temp->env_element, cmd_args[i],
					ft_strlen(cmd_args[i])))
			{
				unset = temp;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(unset);
				break ;
			}
			i++;
		}
		temp = temp->next;
	}
}
