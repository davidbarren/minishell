/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:26:05 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/24 14:47:25 by plang            ###   ########.fr       */
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
//
//void	make_redirect_node(t_redir **redir, char *str, int len)
//{
//	t_redir	*new;
//	t_redir	*last;
//
//	new = ft_calloc (1, sizeof(t_redir));
//	if (!new)
//		return ;
//	new->index = 0;
//	new->next = NULL;
//	new->str = ft_strndup(str, len, 0);
//	if (!new->str)
//		return ;
//	if (!*redir)
//		*redir = new;
//	else
//	{
//		last = get_last_redir(*redir);
//		last->next = new;
//		new->index = last->index + 1;
//	}
//}
//
//void	clean_redir_node(t_redir **redir, char *cmd)
//{
//	t_redir	*temp;
//	char	*iter;
//
//	temp = *redir;
//	while (temp)
//	{
//		iter = temp->str;
//		if ((ft_strlen(iter) == 1) && (*iter == '<' || *iter == '>'))
//		{
//			temp = temp->next;
//			iter = temp->str;
//			temp->redir_type = 2;
//		}
//		while (*iter == '<' || *iter == '>' || *iter == ' ')
//			iter++;
//		temp->filename = ft_strndup(iter, ft_strlen_mod(iter, ' ') - 1, 0);
//		while (*iter && (*iter != '>' && *iter != '<'))
//			iter++;
//		temp->cmd = ft_strdup(cmd);
//		printf("Filename:%s\n", temp->filename);
//		printf("Command to run:%s\n", temp->cmd);
//		printf("Type of redir:%d\n", temp->redir_type);
//		temp = temp->next;
//	}
//}
