/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:13:37 by plang             #+#    #+#             */
/*   Updated: 2024/04/28 16:40:34 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_env **env, char *cmd_args)
{
	t_env	*temp;
	t_env	*unset;

	temp = *env;
	while (temp != NULL)
	{
		if (!ft_strncmp(temp->env_element, cmd_args, ft_strlen(cmd_args)))
		{
			unset = temp;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(unset);
			break ;
		}
		temp = temp->next;
	}
}

t_env	*ft_getenv(t_env **envs, char *str)
{
	t_env	*temp;

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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*envs;
// 	t_env	*the_one;
// 	char	*no_env;

// 	(void) argc;
// 	(void) argv;
// 	store_env(envp, &envs);
// 	the_one = ft_getenv(&envs, "PATH");
// 	no_env = get_env_str(the_one);
// 	ft_unset(&envs, "PATH");
// 	print_list(envs);
// 	printf("%s\n", the_one->env_element);
// 	printf("%s\n", no_env);
// 	return (0);
// }
