/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:26:05 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/28 16:39:37 by dbarrene         ###   ########.fr       */
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

void	clean_redir_node(t_redir **redir, char *cmd)
{
	t_redir	*temp;
	char	*iterator;

	temp = *redir;
	while (temp)
	{
		iterator = temp->str;
		if ((ft_strlen(iterator) == 1) && (*iterator == '<' || *iterator == '>'))
		{
			temp = temp->next;
			iterator = temp->str;
			temp->redir_type = 2;
		}
		while (*iterator == '<' || *iterator == '>' || *iterator == ' ')
			iterator++;
		temp->filename = ft_strdup(iterator);
		while (*iterator && (*iterator != '>' && *iterator != '<'))
			iterator++;
		temp->cmd = ft_strdup(cmd);
		printf("Filename:%s\n", temp->filename);
		printf("Command to run:%s\n", temp->cmd);
		printf("Type of redir:%d\n", temp->redir_type);
		temp = temp->next;
	}
}

char	*get_cmd_filename_last(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
//	i--;
	while (str[i] != ' ')
		i--;
	return (ft_strndup(str, i));
}

char	*get_file_filename_last(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
//	i--;
	while (str[i] != ' ')
		i--;
	str += i;
	return (ft_strdup(str));
//	while (str[i] && str[i] != '<' && str[i] != '>')
//		j++;
//	return (ft_strndup(str, j));
}
