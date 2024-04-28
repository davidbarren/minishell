/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:00:26 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/28 16:41:18 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_child_command(t_args *args)
{
	char	**ep;
	char	**split_path;
	int		i;

	i = 0;
	args->split_cmds = ft_quotesplit(args->long_command, ' ');
	split_path = ft_split(getenv("PATH"), ':');
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
		}
	}
	execve(split_path[i], args->split_cmds, ep);
}
/*
char	**copy_2d(char **src)
{
	char	**dest;
	int		i;
	int		len;

	len = ft_arrlen(src);
	dest = malloc (sizeof (char *) * (len + 1));
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = 0;
	return (dest);
}
*/

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

void	copy_env(char **ep, t_env **env)
{
	int	len;

	len = get_env_len(*env);
}
