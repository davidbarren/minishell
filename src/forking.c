/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:00:26 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/03 15:24:36 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_child_command(t_args *args)
{
	char	**ep;
	char	**split_path;
	int		i;
	char	*path;

	ep = NULL;
	i = 0;
	printf("Long command: %s\n", args->long_command);
	args->split_cmds = ft_quotesplit(args->long_command, ' '); //should be splitquotes to preserve
														  //arguments inside a quote
														  //e.g. grep -e "Hello world"
														  //hello world has to be 1 argument
														  //instead of 2
//	printf("%s\n", args->split_cmds[0]);
	int j = 0;
	printf("ei men sorri man\n");
	while (args->split_cmds[j])
	{
		args->split_cmds[j] = trim_input(args->split_cmds[j], '\"');
		printf("Split cmds:%s\n", args->split_cmds[j++]);
	}
	path = ft_getenv(args->envlist, "PATH");
	split_path = ft_split(path, ':');
	ep = copy_env(ep, args->envlist);
	i = 0;
	free (path);
//	int saatana = 0;
//	while (ep[saatana])
//	{
//		printf("Address of EP:%p\n With content:%s\n", &ep[saatana], ep[saatana]);
//		saatana++;
//	}
	while (split_path[i])
	{
		printf("Address of split path: %p", &split_path[i]);
		split_path[i] = ft_strjoin_sep(split_path[i], args->split_cmds[0], '/');
		if (access(split_path[i], F_OK))
			i++;
		else
		{
			free(args->long_command);
			args->long_command = ft_strdup(split_path[i]);
			free_2d(split_path);
			printf("Path in prepchild: %s\n", args->long_command);
			int k = 0;
			while (args->split_cmds[k])
				printf("Command in prepchild: %s\n", args->split_cmds[k++]);
			execve(args->long_command, args->split_cmds, ep);
			printf("execve has failed!\n");
		}
	}
	free_2d(ep);
	if (split_path)
		free_2d(split_path);
}

static	int	get_env_len(t_env *env)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

char	**copy_env(char **ep, t_env **env)
{
	int		len;
	int		i;
	t_env	*temp;

	temp = *env;
	i = 0;
	len = get_env_len(*env);
	ep = ft_calloc((len + 1), sizeof (char *));
	while (temp)
	{
		ep[i] = ft_strdup(temp->env_element);
		i++;
		temp = temp->next;
	}
	ep[i] = NULL;
	return (ep);
}
