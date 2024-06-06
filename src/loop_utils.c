/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:16:59 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/06 15:43:48 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	input_valid_routine(t_input *input, char *line)
{
	prep_input(line, input);
	free_structs(input->arg_struct, input->pipe_count);
}

char	*env_join_sep(char *s1, char *s2, char sep)
{
	char	*joined;
	int		i;

	if (!s2)
		return (ft_strdup(s1));
	if (!s1 || !s2 || sep == '\0')
		return (NULL);
	i = 0;
	joined = malloc (ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!joined)
		return (NULL);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i++] = sep;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = 0;
	return (joined);
}

void	ft_update_shlvl(t_env **envs)
{
	int		level;
	t_env	*shlvl;

	shlvl = getenv_node(envs, "SHLVL");
	if (!shlvl)
		return ;
	level = ft_atoi(shlvl->info);
	free(shlvl->info);
	level += 1;
	if (level < 0)
		level = 0;
	shlvl->info = ft_itoa(level);
	free(shlvl->env_element);
	shlvl->env_element = env_join_sep(shlvl->title, shlvl->info, '=');
}
