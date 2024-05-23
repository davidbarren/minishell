/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:44:23 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/23 13:37:27 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	files_and_dups(t_redir *node)
{
	if (node->redir_type == 4)
		node->fd = open(node->str, O_CREAT | O_APPEND | O_RDWR, 0644);
	else if (node->redir_type != 1)
		node->fd = open(node->str, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (node->redir_type == 1)
		node->fd = open(node->str, O_CREAT | O_RDONLY, 0644);
	if (node->fd == -1)
		dprintf(2, "error creating file in node:%s\n", node->str);
	if (node->redir_type == 1)
	{
		if (dup2(node->fd, STDIN_FILENO) == -1)
			dprintf(2, "error duping STDIN in node :%s\n", node->str);
	}
	else
	{
		if (dup2(node->fd, STDOUT_FILENO) == -1)
			dprintf(2, "error duping STDOUT in node :%s\n", node->str);
	}
	close(node->fd);
}

void	redirs_iteration(t_redir **redirs)
{
	t_redir	*temp;

	temp = *redirs;
	while (temp)
	{
		files_and_dups(temp);
		temp = temp->next;
	}
}

void	space_insertion(char *prepped, char *source)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (source[i])
	{
		if (!ft_strncmp(source + i, ">>", 2))
		{
			prepped[k + i] = ' ';
			prepped[k + i + 1] = source[i];
			prepped[k + i + 2] = source[i];
			prepped[k + i + 3] = ' ';
			k += 2;
			i += 2;
		}
		else if ((source[i] == '<' || source[i] == '>')
			&& (ft_strncmp(source + i, ">>", 3)))
		{
			prepped[k + i] = ' ';
			prepped[k + i + 1] = source[i];
			prepped[k + i + 2] = ' ';
			k += 2;
			i++;
		}
		else
		{
			prepped[k + i] = source[i];
			i++;
		}
	}
}
/*
   void	create_files(t_redir *temp, t_redir *output_node)
   {
//	if (access(temp->filename, W_OK | R_OK))
//		exit (69);
if (temp->redir_type == 2)
temp->fd = open(temp->str, O_CREAT | O_APPEND | O_RDWR, 0644);
else
temp->fd = open(temp->str, O_CREAT | O_TRUNC | O_RDWR, 0644);
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

void	redir_fd_modifying(t_redir **redir)
{
	t_redir	*input_node;
	t_redir	*output_node;

	input_node = *redir;
	output_node = get_last_redir(*redir);
	printf("contents of input node:%s\n", input_node->filename);
	printf("contents of output node:%s\n", output_node->filename);
	dup2(output_node->fd, STDOUT_FILENO);
	close(output_node->fd);
}

*/
