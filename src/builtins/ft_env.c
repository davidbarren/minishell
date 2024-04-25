/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:54:24 by plang             #+#    #+#             */
/*   Updated: 2024/04/23 18:10:07 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>// remove

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*env_element;
	int				index;
}	t_env;

typedef struct s_args
{
	// t_redir			**redirects;
	// t_redir			**heredoc;
	char			*arglist;
	char			**split_cmds;
	int				cmd_index;
	char			*tokenized_args;
	char			*long_command;
	int				redir_count;
	int				token_count;
	int				has_redir;
	pid_t			*pids;
}	t_args;

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
// 		i++;
// 	return (s1[i] - s2[i]);
// }

int	ft_env(t_env **env)
{
	t_env	*temp;
	int		status;

	temp = *env;
	status = 0;
	if (temp)
	{
		while (temp->next != NULL)
		{
			printf("%s\n", temp->env_element);
			temp = temp->next;
		}
	}
	else
		status = 1;
	return (status);
}
