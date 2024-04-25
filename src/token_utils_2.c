/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:26:05 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/23 17:46:01 by dbarrene         ###   ########.fr       */
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
			free (temp->str);
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

static t_redir	*get_last_redir(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	make_redirect_node(t_redir **redir, char *str, int len)
{
	t_redir	*new;
	t_redir	*last;

	new = calloc (1, sizeof(t_redir));
	if (!new)
		return ;
	new->index = 0;
	new->next = NULL;
	new->str = ft_strndup(str, len);
	if (!new->str)
		return ;
	if (!*redir)
		*redir = new;
	else
	{
		last = get_last_redir(*redir);
		last->next = new;
		new->index = last->index + 1;
	}
}
