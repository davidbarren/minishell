/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:37:22 by plang             #+#    #+#             */
/*   Updated: 2024/04/25 13:42:12 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*env_element;
	int				index;
}	t_env;

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
// 		i++;
// 	return (s1[i] - s2[i]);
// }

void	ft_unset(t_env **env, char **cmd_args)
{
	t_env	*temp;
	t_env	*unset;
	int		i;

	temp = *env;
	while (temp != NULL)
	{
		i = 1;
		while (cmd_args[i])
		{
			if (!ft_strncmp(temp->env_element, cmd_args[i], ft_strlen(cmd_args[i])))
			{
				unset = temp;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(unset);
				break ;
			}
			i++;
		}
		temp = temp->next;
	}
}

	// string, argument after the command. strcmp to the environment linked list
	// take in environment list and 2d array of command and argument.
	