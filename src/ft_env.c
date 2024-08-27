/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:54:24 by plang             #+#    #+#             */
/*   Updated: 2024/06/25 17:24:49 by plang            ###   ########.fr       */
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
				ft_printf("%s=%s\n", temp->title, temp->info);
			temp = temp->next;
		}
		return (0);
	}
	else
		return (1);
}
