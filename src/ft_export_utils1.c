/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:51:45 by plang             #+#    #+#             */
/*   Updated: 2024/06/25 17:25:17 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

void	clean_from_quotes(char **str)
{
	char	*copy;
	char	*start;
	int		i;
	int		equal;

	i = 0;
	equal = 0;
	while ((*str)[equal] != '=' && (*str)[equal])
		equal++;
	copy = ft_strdup(*str);
	if (!copy)
		return ;
	start = copy;
	while (*copy)
	{
		if (*copy != '"' && *copy != '\'')
			(*str)[i++] = *copy;
		else if (i > equal)
			(*str)[i++] = *copy;
		copy++;
	}
	(*str)[i] = '\0';
	free(start);
}

void	ft_export_clean(char **cmd_args)
{
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		clean_from_quotes(&cmd_args[i]);
		i++;
	}
}

void	change_lists_content(t_env **envs, char *new_env_str)
{
	t_env	*temp;
	int		what_env;

	temp = *envs;
	while (temp != NULL)
	{
		what_env = 0;
		if (!ft_strchr(new_env_str, '='))
			return ;
		while (new_env_str[what_env] != '=' && new_env_str[what_env])
			what_env++;
		if (!check_duplicate_env(temp->title, new_env_str, what_env))
		{
			free(temp->env_element);
			free(temp->title);
			free(temp->info);
			temp = store_export_title_n_info(temp, new_env_str);
			break ;
		}
		temp = temp->next;
	}
}

int	find_equal_sign(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

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
