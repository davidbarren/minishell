/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:54:24 by plang             #+#    #+#             */
/*   Updated: 2024/06/05 17:25:59 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_env **env)
{
	t_env	*temp;

	temp = *env;
	if (temp)
	{
		while (temp)
		{
			if (temp->info)
				printf("%s\n", temp->env_element);
			temp = temp->next;
		}
		return (0);
	}
	else
		return (1);
}
