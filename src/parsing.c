/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:15:18 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/03 14:56:44 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_last_node(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	parse_input(char **ep, t_env **env)
{
	store_env(ep, env);
	store_env_title_n_info(env);
}

void	store_env(char **ep, t_env **env)
{
	int	i;

	i = 0;
	while (ep[i])
	{
		add_env_to_back(env, ep[i], i);
		i++;
	}
}

void	print_list(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		printf("%s\n index:%d\n", temp->env_element, temp->index);
		temp = temp->next;
	}
}

int	count_redirects(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i]) == '>' || str[i] == '<')
			count++;
		i++;
		if ((str[i]) == '>' || str[i] == '<')
			i++;
	}
	return (count);
}

void	free_list(t_env **env)
{
	t_env	*next;

	next = *env;
	if (!*env) 
		return ;
	while (next)
	{
		next = next->next;
		free_content(*env);
		free (*env);
		*env = next;
	}
}

void	free_content(t_env *env)
{

	if (env->env_element)
		free(env->env_element);
	if (env->title)
		free(env->title);
	if (env->info)
		free(env->info);
//	if (env->next)
//		free(env->next);
//	if (env->prev)
//		free(env->prev);

}
