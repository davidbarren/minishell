/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:00:26 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/15 11:05:02 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	get_env_len(t_env *env)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

char	**copy_env(char **ep, t_env **env)
{
	int		len;
	int		i;
	t_env	*temp;

	temp = *env;
	i = 0;
	len = get_env_len(*env);
	ep = ft_calloc((len + 1), sizeof (char *));
	while (temp)
	{
		ep[i] = ft_strdup(temp->env_element);
		i++;
		temp = temp->next;
	}
	ep[i] = NULL;
	return (ep);
}
