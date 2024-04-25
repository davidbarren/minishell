/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:54:24 by plang             #+#    #+#             */
/*   Updated: 2024/04/25 15:00:22 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env **env)
{
	t_env	*temp;
	int		status;

	temp = *env;
	status = 0;
	if (temp)
	{
		while (temp->next != NULL)
		{
			printf("%s\n", temp->env_element);
			temp = temp->next;
		}
	}
	else
		status = 1;
	return (status);
}
