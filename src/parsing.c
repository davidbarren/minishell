/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:15:18 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/05 15:22:09 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_input(char **ep, t_env *env)
{
	store_env(ep, &env);
}
void	store_env(char **ep, t_env **env)
{
	int i;
	i = 0;
	while (ep[i])
	{
		*env = add_env_to_back(*env, ep[i]);
		i++;
	}
}

t_env	*add_env_to_back(t_env *env, void *data)
{
	t_env	*last_node;
	t_env	*new_node;
	t_env	*temp;
	temp = env;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env_element = data;
	new_node->next = NULL;
	if (!env)
	{
		env = new_node;
		new_node->prev = NULL;
	}
	else
	{
		last_node = get_last_node(env);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	return (env);
}

t_env	*get_last_node(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

