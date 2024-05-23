/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:51:49 by plang             #+#    #+#             */
/*   Updated: 2024/05/23 11:54:23 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

int	export_validation(char *args)
{
	if (args[0] == '=')
		return (1);
	if (!ft_isalpha(args[0]))
		return (1);
	return (0);
}

int	export_no_args(t_env **envs)
{
	t_env	*temp;

	temp = *envs;
	while (temp)
	{
		if (temp->title != NULL && temp->info != NULL)
		{
			printf("declare -x %s", temp->title);
			printf("=\"%s\"\n", temp->info);
		}
		else if (temp->title != NULL && temp->info == NULL)
		{
			printf("declare -x %s\n", temp->title);
		}
		else if (temp->env_element != NULL)
			printf("declare -x %s\n", temp->env_element);
		temp = temp->next;
	}
	return (1);
}

int	check_duplicate_env(char *env_list_str, char *export_str, int what_env)
{
	int	i;

	i = 0;
	while (env_list_str[i] != '=' && env_list_str[i])
		i++;
	if (!export_str || !env_list_str)
		return (0);
	if (i != what_env)
		return (1);
	if (ft_strncmp(env_list_str, export_str, what_env))
		return (1);
	return (0);
}

t_env	*store_export_title_n_info(t_env *new_node, char *str)
{
	int		i;
	int		title_len;

	i = 0;
	title_len = 0;
	new_node->env_element = ft_substr(str, 0, ft_strlen(str));
	if (!new_node->env_element)
		return (NULL);
	while (str[title_len] != '=' && str[title_len])
		title_len++;
	new_node->title = ft_substr(str, 0, (title_len));
	if (!new_node->title)
		return (NULL);
	new_node->info = ft_substring(str, (title_len + 1), \
	(ft_strlen(str) - title_len));
	clean_from_quotes(&new_node->info);
	if (!new_node->info)
		return (NULL);
	return (new_node);
}
