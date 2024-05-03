/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:34:45 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/03 10:51:08 by dbarrene         ###   ########.fr       */
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
	while (str[i] != ' ')
		i--;
	str += i;
	return (ft_strdup(str));
}

void	file_opening(t_redir *redir, t_args *args)
{
	t_redir *temp;
	int macaco = 0;
	if (args)
		macaco = 1;
	temp = redir;

//	if (!temp->index || redir->index == args->redir_count)
//		temp->fd_in = open(temp->filename, O_RDWR);
	while (temp)
	{
		temp->fd_status = open(redir->filename, O_CREAT);
		if (temp->fd_status == -1)
			ft_printerror("Error creating file");
		else
			close (temp->fd_status);
		temp = temp->next;
	}
}
/*
we  should open every single "passenger" fd and create the file and then ignore;
 * content from the first file in the redir linked list should be passed to
 * the LAST element in the redir LL directly thru dup2() of stdin and stdout
*/

