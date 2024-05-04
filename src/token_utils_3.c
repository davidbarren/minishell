/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:34:45 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/04 22:01:53 by dbarrene         ###   ########.fr       */
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
	return (ft_strndup(str, i, 1));
}

char	*get_file_filename_last(char *str)
{
	int	i;
	int	j;
	char *temp;

	temp = str;
	i = 0;
	j = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	while (str[i] != ' ')
		i--;
	str += i;
	free(temp);
	printf("address of str in getfilenamelast:%p\n", str);
	printf("address of temp in getfilenamelast:%p\n", temp);
	return (ft_strdup(str));
}

void	file_opening(t_redir *redir, t_args *args)
{
	(void) args;
	t_redir *temp;
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

