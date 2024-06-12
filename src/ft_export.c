/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:49 by plang             #+#    #+#             */
/*   Updated: 2024/06/12 15:28:28 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

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

void	adding_to_last_node(t_env **envs, t_env *new_node)
{
	t_env	*last_node;

	last_node = get_last_node(*envs);
	last_node->next = new_node;
	new_node->prev = last_node;
}

void	add_export_to_list(t_env **envs, char *str)
{
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
			adding_to_last_node(envs, new_node);
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
	int		i;
	int		status;

	status = 0;
	if (!cmd_args[1] && export_no_args(envs))
		return (status);
	i = 1;
	while (cmd_args[i])
	{
		if (!export_validation(cmd_args[i]))
		{
			export_is_valid(envs, cmd_args, &i);
		}
		else
		{
			ft_printerror("🐒: export: `%s': not a valid identifier\n",
				cmd_args[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
