/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:48 by plang             #+#    #+#             */
/*   Updated: 2024/06/06 19:20:29 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	assign_expanded(char **arg, char *expanded, char *beginning)
{
	if (!expanded)
		*arg = ft_strdup("");
	else
		*arg = expanded;
	if (beginning)
		*arg = ft_strjoin_flex(beginning, expanded, 3);
}

void	expand_check_arguments(t_env **envs, char **arg, int es)
{
	int			i;
	char		*expanded;
	int			qflag;
	char		*beginning;

	i = 0;
	qflag = get_qflag(*arg);
	beginning = 0;
	if ((*arg)[0] != '$' && ft_strchr((*arg), '$') && qflag < 2)
		beginning = get_beginning((*arg));
	while ((*arg)[i] != '\0')
	{
		if ((*arg)[i] == '$' && qflag < 2 && (*arg)[i + 1] != '\0')
		{
			i++;
			expanded = is_expansion_valid(envs, *arg, i, es);
			free(*arg);
			assign_expanded(arg, expanded, beginning);
			if (ft_strchr((*arg), '$') && qflag < 2)
				expand_rest(envs, arg, &i, es);
			break ;
		}
		i++;
	}
}

void	expand_and_join(t_env **envs, char **s_cmds, char **part_array, int es)
{
	int	j;

	j = 0;
	while (part_array[j] != NULL)
	{
		expand_check_arguments(envs, &part_array[j], es);
		j++;
	}
	j = 0;
	free(*s_cmds);
	*s_cmds = part_array[j];
	while (part_array[j + 1] != NULL)
	{
		(*s_cmds) = ft_strjoin_flex(*s_cmds, part_array[j + 1], 3);
		j++;
	}
	free(part_array);
}

void	find_expansion(t_env **envs, char **split_cmds, int es)
{
	int		parts;
	char	**part_array;
	int		j;
	int		start;
	int		len;

	j = 0;
	start = 0;
	parts = how_many_parts(*split_cmds);
	part_array = malloc((parts + 1) * sizeof(char *));
	if (!part_array)
		return ;
	while (parts > j)
	{
		len = get_part_len(*split_cmds, start);
		part_array[j] = ft_substr(*split_cmds, start, len);
		start += ft_strlen(part_array[j]);
		j++;
	}
	part_array[j] = 0;
	expand_and_join(envs, split_cmds, part_array, es);
}

void	ft_expand(char **split_cmds, t_env **envlist, int es)
{
	int	j;

	j = 0;
	while (split_cmds[j] != NULL)
	{
		if (ft_strchr(split_cmds[j], '$'))
			find_expansion(envlist, &split_cmds[j], es);
		j++;
	}
}
