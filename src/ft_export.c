/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:49 by plang             #+#    #+#             */
/*   Updated: 2024/05/08 17:13:24 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		printf("Address of temp:%p\n", temp);
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
/*
int	export_no_args(t_env **envs)
{
	t_env	*temp;

	temp = *envs;
	while (temp != NULL)
	{
		printf("address of title:%p\n address of info:%p\n address of envelement:%p\n",temp->title, temp->info, temp->env_element);
//		if (temp->title && temp->info)
//			printf("declare -x %s=\"%s\"\n", temp->title, temp->info);
//		else if (temp->title)
//			printf("declare -x %s=\"\n", temp->title);
//		else if (temp->info)
//			printf("declare -x %s=\"\n", temp->info);
		temp = temp->next;
	}
	return (1);
}
*/
int	check_duplicate_env(char *env_list_str, char *export_str, int what_env)
{
	int	i;

	i = 0;
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
	new_node->info = ft_substr(str, (title_len + 1), \
	(ft_strlen(str) - title_len));
	if (!new_node->info)
		return (NULL);
	return (new_node);
}

void	change_lists_content(t_env **envs, char *new_env_str)
{
	t_env	*temp;
	int		what_env;

	temp = *envs;
	while (temp != NULL)
	{
		what_env = 0;
		while (new_env_str[what_env] != '=' && new_env_str[what_env])
			what_env++;
		if (!check_duplicate_env(temp->env_element, new_env_str, what_env))
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

void	only_export_title(t_env **envs, char *str)
{
	t_env	*last_node;
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->title = ft_strdup(str);
	if (!new_node->title)
		return ;
	new_node->next = NULL;
	last_node = get_last_node(*envs);
	last_node->next = new_node;
	new_node->prev = last_node;
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

int	ft_export(t_env **envs, char **cmd_args)
{
	t_env	*temp;
	int		i;
	int		what_env;
	int		flag;

	temp = *envs;
	flag = 0;
	ft_export_clean(cmd_args);
	if (!cmd_args[1] && export_no_args(envs))
		return (0); //EXIT_SUCCESS
	i = 1;

	while (cmd_args[i])
	{
		if (!export_validation(cmd_args[i]))
		{
			while (temp != NULL)
			{
				what_env = 0;
				while (cmd_args[i][what_env] != '=' && cmd_args[i][what_env])
					what_env++;
				if (!check_duplicate_env(temp->title, cmd_args[i], what_env))
					flag = 1;
				temp = temp->next;
			}
			temp = *envs;
			if (flag == 1)
			{
				change_lists_content(envs, cmd_args[i]);
				flag = 0;
			}
			else if (flag == 0)
				add_export_to_list(envs, cmd_args[i]);
		}
		else
			printf("baboonshell: export: `%s': not a valid identifier\n", cmd_args[i]);
		i++;
	}
	return (0); //EXIT_SUCCESS
}

