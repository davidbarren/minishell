/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:17:30 by plang             #+#    #+#             */
/*   Updated: 2024/04/30 13:37:14 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	store_env_title_n_info(t_env **env)
{
	int		i;
	int		title_len;
	t_env	*temp;

	i = 0;
	temp = *env;
	while (temp != NULL)
	{
		title_len = 0;
		while (temp->env_element[title_len] != '=')
			title_len++;
		temp->title = ft_substring(temp->env_element, 0, (title_len));
		if (!temp->title)
			return ;
		temp->info = ft_substring(temp->env_element, (title_len + 1), \
		(ft_strlen(temp->env_element) - title_len));
		if (!temp->info)
			return ;
		temp = temp->next;
	}
}

void	add_env_to_back(t_env **env, char *data, int index)
{
	t_env	*last_node;
	t_env	*new_node;
	t_env	*temp;

	temp = *env;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->env_element = ft_strdup(data);
	new_node->index = index;
	if (!new_node->env_element)
		return ;
	new_node->next = NULL;
	if (!*env)
	{
		new_node->prev = NULL;
		*env = new_node;
	}
	else
	{
		last_node = get_last_node(*env);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}
