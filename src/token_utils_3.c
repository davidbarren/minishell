/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:34:45 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/07 16:55:47 by dbarrene         ###   ########.fr       */
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
	int	i;
	int	j;
	char *temp;

	printf("Address of str in get_file_filename last %p\n", str);

	temp = str;
	i = 0;
	j = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	while (str[i] != ' ')
		i--;
	str += i;
//	free(temp);
	return (ft_strdup(str));
}

void	file_opening(t_redir *redir, t_args *args)
{
	(void) args;
	t_redir *temp;
	t_redir *output_node;

	output_node = get_last_redir(redir);
	temp = redir;
	while (temp)
	{
		if (temp->redir_type == 2)
			temp->fd_status = open(temp->filename, O_CREAT, 0644);
		else
			temp->fd_status = open(temp->filename, O_CREAT | O_TRUNC, 0644);
		if (temp->fd_status == -1)
			ft_printerror("Error creating file");
		/* this if statment makes it hang, need to fix
//		if (temp == output_node)
//		{
//			dup2(temp->fd_status, STDOUT_FILENO);
//			close (temp->fd_status);
//		}*/
		else
			close (temp->fd_status);
		temp = temp->next;
	}
}
/*
 * currently the filenames contain extra spaces and the linkedlist creates
 * an empty node at first, probably should fix that :DDD
we  should open every single "passenger" fd and create the file and then ignore;
 * content from the first file in the redir linked list should be passed to
 * the LAST element in the redir LL directly thru dup2() of stdin and stdout
*/

void	redir_fd_modifying(t_redir **redir)
{
	t_redir *input_node;
	t_redir *output_node;

	input_node = *redir;
	output_node = get_last_redir(*redir);
	printf("contents of input node:%s\n", input_node->filename);
	printf("contents of output node:%s\n", output_node->filename);
//	dup2(input_node->fd_status, STDIN_FILENO);
//	close(input_node->fd_status);
	dup2(output_node->fd_status, STDOUT_FILENO);
	close(output_node->fd_status);

}
/* only thing that gets dup'ed should be stdout being replaced by the fd
 * of the last redir node's file's fd
 * right?
 *
 * currently it hangs and doesn't copy the info properly :(
 */
