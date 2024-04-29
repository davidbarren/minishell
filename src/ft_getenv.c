/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:13:37 by plang             #+#    #+#             */
/*   Updated: 2024/04/29 18:10:26 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*getenv_node(t_env **envs, char *str)
{
	t_env	*temp;
	if (!*envs)
		return (NULL);
	temp = *envs;
	while (temp != NULL)
	{
		if (!ft_strncmp(temp->env_element, str, ft_strlen(str)))
			break ;
		temp = temp->next;
	}
	return (temp);
}

char	*get_env_str(t_env *complete_env)
{
	char	*extracted;
	int		start;
	int		end;
	int		len;
	int		i;

	start = 0;
	while (complete_env->env_element[start] != '=')
		start++;
	start++;
	end = ft_strlen(complete_env->env_element);
	len = end - start;
	extracted = malloc((len + 1) * sizeof(char));
	if (!extracted)
		return (NULL);
	i = 0;
	while (start < end)
	{
		extracted[i] = complete_env->env_element[start];
		i++;
		start++;
	}
	extracted[i] = '\0';
	return (extracted);
}

char    *ft_getenv(t_env **envs, char *str)
{
    t_env    *node;
    char    *env_str;
//	printf("Address of envs in ft_getenv:%p\n", envs);
//	printf("Address of envs dereferenced in ft_getenv:%p\n", *envs);
    node = getenv_node(envs, str);
    env_str = get_env_str(node);
    return (env_str);
}
