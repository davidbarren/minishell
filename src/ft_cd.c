/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:54:36 by plang             #+#    #+#             */
/*   Updated: 2024/06/05 17:25:39 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

t_env	*store_pwd_title_n_info(t_env *new_node, char *title_path)
{
	int		i;
	int		title_len;

	i = 0;
	title_len = 0;
	new_node->env_element = ft_substr(title_path, 0, ft_strlen(title_path));
	if (!new_node->env_element)
		return (NULL);
	while (title_path[title_len] != '=' && title_path[title_len])
		title_len++;
	new_node->title = ft_substr(title_path, 0, (title_len));
	if (!new_node->title)
		return (NULL);
	new_node->info = ft_substring(title_path, (title_len + 1), \
	(ft_strlen(title_path) - title_len));
	if (!new_node->info)
		return (NULL);
	return (new_node);
}

void	change_oldpwd_pwd(t_env **envs, char *title_n_path)
{
	t_env	*temp;
	int		what_env;

	temp = *envs;
	while (temp != NULL)
	{
		what_env = 0;
		if (!ft_strchr(title_n_path, '='))
			return ;
		while (title_n_path[what_env] != '=' && title_n_path[what_env])
			what_env++;
		if (!check_duplicate_env(temp->title, title_n_path, what_env))
		{
			free(temp->env_element);
			free(temp->title);
			free(temp->info);
			temp = store_pwd_title_n_info(temp, title_n_path);
			break ;
		}
		temp = temp->next;
	}
}

void	update_paths(t_env **envs, char *path, char *title)
{
	t_env	*temp;
	char	*combined;

	temp = *envs;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->title, title, ft_strlen(title)))
		{
			combined = ft_strjoin(title, path);
			change_oldpwd_pwd(envs, combined);
			free(combined);
			break ;
		}
		temp = temp->next;
	}
}

int	ft_cd(t_env **envs, char **cmd_args)
{
	char	cwd[2000];
	char	*oldpwd;
	char	*temp;

	oldpwd = getcwd(cwd, sizeof(cwd));
	if (!cmd_args[1] || ft_strchr(cmd_args[1], '~'))
	{
		temp = ft_getenv(envs, "HOME");
		chdir(temp);
		if (!ft_getenv(envs, "HOME"))
			printf("🐒: cd: HOME not set\n");
		free(temp);
		temp = NULL;
	}
	else if (chdir(cmd_args[1]) == -1)
	{
		ft_putstr_fd("🐒: cd: ", 2);
		ft_putstr_fd(cmd_args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	update_paths(envs, oldpwd, "OLDPWD=");
	update_paths(envs, getcwd(cwd, sizeof(cwd)), "PWD=");
	return (0);
}
