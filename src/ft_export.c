/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:49 by plang             #+#    #+#             */
/*   Updated: 2024/04/29 16:51:15 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_duplicate_env(char *env_list_str, char *export_str, int what_env)
{
	int	i;

	i = 0;
	if (ft_strncmp(env_list_str, export_str, what_env))
		return (1);
	return (0);
}

void	change_lists_content(t_env **envs, char *new_env_str)
{
	t_env	*temp;
	int		what_env;

	temp = *envs;
	while (temp != NULL)
	{
		what_env = 0;
		while (new_env_str[what_env] != '=')
			what_env++;
		if (!check_duplicate_env(temp->env_element, new_env_str, what_env))
		{
			free(temp->env_element);
			temp->env_element = ft_strdup(new_env_str);
			break ;
		}
		temp = temp->next;
	}
}

void	add_export_to_list(t_env **envs, char *str)
{
	t_env	*last_node;
	t_env	*new_node;
	t_env	*temp;
	
	temp = *envs;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->env_element = ft_strdup(str);
	if (!new_node->env_element)
		return ;
	new_node->next = NULL;
	if (!*envs)
	{
		new_node->prev = NULL;
		*envs = new_node;
	}
	else
	{
		last_node = get_last_node(*envs);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}

void	ft_export(t_env **envs, char **cmd_args)
{
	t_env	*temp;
	int		i;
	int		what_env;
	int		flag;

	temp = *envs;
	flag = 0;
	while (temp != NULL)
	{
		i = 1;
		what_env = 0;
		while (cmd_args[i][what_env] != '=')
			what_env++;
		if (!check_duplicate_env(temp->env_element, cmd_args[i], what_env))
				flag = 1;
		temp = temp->next;
	}
	if (flag == 0)
		add_export_to_list(envs, cmd_args[i]);
	else if (flag == 1)
		change_lists_content(envs, cmd_args[i]);
}
