/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:26:05 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/04 17:25:34 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	extract_cmds(t_args *args)
{
	t_redir	*temp;

	if (!args->redir_count)
		return ;
	temp = *(args->redirects);
	while (temp)
	{
		if (ft_strnstr(temp->str, args->long_command, ft_strlen(temp->str)))
		{
			temp->str = ft_strdup(args->tokenized_args);
		}
		temp = temp->next;
	}
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_redir	*get_last_redir(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	space_insertion(char *prepped, char *s, int i, int k)
{
	while (s[i])
	{
		if (!ft_strncmp(s + i, ">>", 2) || (!ft_strncmp(s + i, "<<", 2)))
		{
			prepped[k + i] = ' ';
			prepped[k + i + 1] = s[i];
			prepped[k + i + 2] = s[i];
			prepped[k + i + 3] = ' ';
			k += 2;
			i += 2;
		}
		else if ((s[i] == '<' || s[i] == '>') && (ft_strncmp(s + i, ">>", 3)))
		{
			prepped[k + i] = ' ';
			prepped[k + i + 1] = s[i];
			prepped[k + i + 2] = ' ';
			k += 2;
			i++;
		}
		else
		{
			prepped[k + i] = s[i];
			i++;
		}
	}
}
