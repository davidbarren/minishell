/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:34:45 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/07 11:39:44 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	file_opening(t_redir *redir)
{
	t_redir	*temp;
	t_redir	*output_node;

	output_node = get_last_redir(redir);
	temp = redir;
	while (temp)
	{
		create_files(temp, output_node);
		temp = temp->next;
	}
}

void	create_files(t_redir *temp, t_redir *output_node)
{
	if (temp->redir_type == 2)
		temp->fd = open(temp->filename, O_CREAT | O_APPEND | O_RDWR, 0644);
	else
		temp->fd = open(temp->filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (temp->fd == -1)
		ft_printerror("Error creating file");
	if (temp == output_node)
	{
		if (dup2(temp->fd, STDOUT_FILENO) == -1)
		{
			ft_printerror("dup failed you baboon!\n");
			exit (1);
		}
		close (temp->fd);
	}
	else
		close (temp->fd);
}
