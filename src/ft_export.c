/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:49 by plang             #+#    #+#             */
/*   Updated: 2024/05/30 17:29:30 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

void	create_titleonly_node(t_env **envs, char *str, int flag)
{
	t_env	*new_node;
	t_env	*last_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->info = NULL;
	new_node->env_element = NULL;
	new_node->next = NULL;
	new_node->title = ft_strdup(str);
	if (!new_node->title)
		return ;
	if (!flag)
	{
		last_node = get_last_node(*envs);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	else
	{
		new_node->prev = NULL;
		*envs = new_node;
	}
}

void	only_export_title(t_env **envs, char *str)
{
	t_env	*temp;

	temp = *envs;
	if (!temp)
		create_titleonly_node(envs, str, 1);
	while (temp)
	{
		if (ft_strcmp(temp->title, str))
		{
			create_titleonly_node(envs, str, 0);
			break ;
		}
		temp = temp->next;
	}
}

void	add_export_to_list(t_env **envs, char *str)
{
	t_env	*last_node;
	t_env	*new_node;

	if (find_equal_sign(str))
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		new_node = store_export_title_n_info(new_node, str);
		if (!new_node)
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
	else if (!find_equal_sign(str))
		only_export_title(envs, str);
}

void	export_is_valid(t_env **envs, char **cmd_args, int *i)
{
	t_env	*temp;
	int		what_env;
	int		flag;

	temp = *envs;
	flag = 0;
	while (temp != NULL)
	{
		what_env = 0;
		while (cmd_args[*i][what_env] != '=' && cmd_args[*i][what_env])
			what_env++;
		if (!check_duplicate_env(temp->title, cmd_args[*i], what_env))
			flag = 1;
		if (flag == 1)
			break ;
		temp = temp->next;
	}
	temp = *envs;
	if (flag == 1)
	{
		change_lists_content(envs, cmd_args[*i]);
	}
	else if (flag == 0)
		add_export_to_list(envs, cmd_args[*i]);
}

int	ft_export(t_env **envs, char **cmd_args)
{
	t_env	*temp;
	int		i;

	temp = *envs;
	int k = 0;
	while (cmd_args[k])
		dprintf(2, "contents of cmd args:%s\n", cmd_args[k++]);
	ft_export_clean(cmd_args);
	if (!cmd_args[1] && export_no_args(envs))
		return (0); //EXIT_SUCCESS
	i = 1;
	while (cmd_args[i])
	{
		if (!export_validation(cmd_args[i]))
		{
			export_is_valid(envs, cmd_args, &i);
		}
		else
			printf("🐒: export: `%s': not a valid identifier\n", cmd_args[i]);
		i++;
	}
	return (0); //EXIT_SUCCESS
}
