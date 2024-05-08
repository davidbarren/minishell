/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:54:24 by plang             #+#    #+#             */
/*   Updated: 2024/05/07 11:35:05 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_env **env)
{
	t_env	*temp;

	temp = *env;
	if (temp)
	{
		while (temp->next != NULL)
		{
			printf("%s\n", temp->env_element);
			temp = temp->next;
		}
		return (0); //EXIT_SUCCESS
	}
	else
		return (1); //EXIT_FAILURE
}
