/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:34:45 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/15 11:35:51 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd_filename_last(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	while (str[i] != ' ')
		i--;
	return (ft_strndup(str, i, 0));
}

char	*get_file_filename_last(char *str)
{
	int		i;
	int		j;
	char	*temp;

	temp = str;
	i = 0;
	j = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	while (str[i] != ' ')
		i--;
	str += i;
	return (ft_strdup(str));
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
