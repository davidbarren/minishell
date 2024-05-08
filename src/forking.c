/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:00:26 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/08 17:29:17 by dbarrene         ###   ########.fr       */
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
//	printf("Long command: %s\n", args->long_command);
	args->split_cmds = ft_quotesplit(args->long_command, ' ');
//	ft_printerror("Command from pcc:%s\n", args->split_cmds[0]);
	while (args->split_cmds[i])
	{
		args->split_cmds[i] = trim_input(args->split_cmds[i], '\"');
		i++;
	}
	path = ft_getenv(args->envlist, "PATH");
	split_path = ft_split(path, ':');
	ep = copy_env(ep, args->envlist);
	i = 0;
	free (path);
	while (split_path[i])
	{
		split_path[i] = ft_strjoin_sep(split_path[i], args->split_cmds[0], '/');
		if (access(split_path[i], F_OK))
			i++;
		else
		{
			free(args->long_command);
			args->long_command = ft_strdup(split_path[i]);
			free_2d(split_path);
			if (execve(args->long_command, args->split_cmds, ep) == -1)
			{
				printf("execve has failed!\n");	
				exit (127);
			}
		}
	}
	ft_printerror("Command not found!\n");
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
