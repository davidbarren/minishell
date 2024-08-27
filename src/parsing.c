/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:15:18 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/25 17:26:08 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_last_node(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	parse_input(char **ep, t_env **env)
{
	store_env(ep, env);
	store_env_title_n_info(env);
}

void	store_env(char **ep, t_env **env)
{
	int	i;

	i = 0;
	while (ep[i])
	{
		add_env_to_back(env, ep[i], i);
		i++;
	}
}

void	print_list(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		ft_printf("%s\n index:%d\n", temp->env_element, temp->index);
		temp = temp->next;
	}
}
