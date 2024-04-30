/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:17:30 by plang             #+#    #+#             */
/*   Updated: 2024/04/30 11:07:50 by plang            ###   ########.fr       */
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
