/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:44:23 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/06 21:27:02 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_hdoc(t_redir *node)
{
	char	*line;

	node->str = ft_strjoin_flex(node->str, "\n", 1);
	node->hdoc_title = ft_strjoin_flex(".hdoc", ft_itoa(node->index), 2);
	node->fd = open(node->hdoc_title, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(1, ">", 1);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, node->str, ft_strlen(node->str)))
			break ;
		write(1, ">", 1);
		ft_putstr_fd(line, node->fd);
		free(line);
		line = get_next_line(0);
	}
	free (line);
	close(node->fd);
}

void	files_and_dups(t_redir *node, int has_cmd)
{
	if (node->redir_type == 4)
		node->fd = open(node->str, O_CREAT | O_APPEND | O_RDWR, 0644);
	else if (node->redir_type != 1)
		node->fd = open(node->str, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (node->redir_type == 1)
	{
		if (access(node->str, O_RDONLY))
		{
			ft_printerror("🐒:%s: No such file or directory\n", node->str);
			return ;
		}
		node->fd = open(node->str, O_RDONLY, 0644);
	}
	if (node->fd == -1)
		exit (-1);
	if (node->redir_type == 1 && has_cmd)
	{
		if (dup2(node->fd, STDIN_FILENO) == -1)
			exit (-1);
	}
	else
		if (dup2(node->fd, STDOUT_FILENO) == -1)
			exit (-1);
	close(node->fd);
}

void	vibe_check(t_redir *temp)
{
	if (!access(temp->str, F_OK))
	{
		if (access(temp->str, O_RDWR))
		{
			ft_printerror("🐒baboonshell: %s: Permission denied\n", temp->str);
			exit (1);
		}
	}
}

void	hdoc_dup_and_close(t_redir *hdoc)
{
	hdoc->fd = open(hdoc->hdoc_title, O_RDONLY, 0644);
	dup2(hdoc->fd, STDIN_FILENO);
	close(hdoc->fd);
	unlink(hdoc->hdoc_title);
}

void	redirs_iteration(t_redir **redirs, int has_cmd)
{
	t_redir	*temp;

	if (!redirs)
		return ;
	temp = *redirs;
	while (temp)
	{
		if (temp->redir_type != 2)
		{
			vibe_check(temp);
			files_and_dups(temp, has_cmd);
		}
		else
			hdoc_dup_and_close(temp);
		temp = temp->next;
	}
}
