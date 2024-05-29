/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:44:23 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/30 02:57:41 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	store_original_fds(t_args *args)
{
	args->original_stdin = dup(STDIN_FILENO);
	args->original_stdout = dup(STDOUT_FILENO);
}
/*
void	close_hdoc(t_redir *node)
{
}
*/
void	create_hdoc(t_redir *node)
{
	char	*line;

//	dprintf(2, "current delim in hdoc:%s\n", node->str);
	node->str = ft_strjoin_flex(node->str, "\n", 1);
	node->fd = open(".hdoc", O_CREAT | O_WRONLY | O_TRUNC , 0644);
	write(1, ">", 1);
	line = get_next_line(0);
	while (line)
	{
		write(1, ">", 1);
//		dprintf(2,"content of line in hdoc test:%s\n", line);
		if (!ft_strncmp(line, node->str, ft_strlen(node->str)))
			break;
		ft_putstr_fd(line, node->fd);
		free(line);
		line = get_next_line(0);
	}
	free (line);
	close(node->fd);
	node->fd = open(".hdoc", O_RDONLY, 0644);
	dup2(node->fd, STDIN_FILENO);
	close (node->fd);
//	close_hdoc(node);
}


void	files_and_dups(t_redir *node, int has_cmd)
{
	dprintf(2, "we really out here duping boii\n");
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
		dprintf(2, "error creating file in node:%s\n", node->str);
	if (node->redir_type == 1 && has_cmd)
	{
		if (dup2(node->fd, STDIN_FILENO) == -1)
			dprintf(2, "error duping STDIN in node :%s\n", node->str);
	}
	else
		if (dup2(node->fd, STDOUT_FILENO) == -1)
			dprintf(2, "error duping STDOUT in node :%s\n", node->str);
	close(node->fd);
}

void	vibe_check(t_redir *temp)
{
	if (!access(temp->str, F_OK))
	{
		if (access(temp->str, O_RDWR))
		{
			ft_printerror("🐒baboonshell: %s: Permission denied", temp->str);
			exit (1);
		}
	}
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
			dprintf(2, "no hdoc yet\n");
			vibe_check(temp);
			files_and_dups(temp, has_cmd);
		}
		else
			create_hdoc(temp);
//			printf("voi vittu!\n");
		temp = temp->next;
	}
}

void	space_insertion(char *prepped, char *s, int i, int k)
{
	while (s[i])
	{
		if (!ft_strncmp(s + i, ">>", 2) || (!ft_strncmp(s + i, "<<", 2)))
		{
			prepped[k + i] = ' ';
			prepped[k + i + 1] = s[i];
			prepped[k + i + 2] = s[i];
			prepped[k + i + 3] = ' ';
			k += 2;
			i += 2;
		}
		else if ((s[i] == '<' || s[i] == '>') && (ft_strncmp(s + i, ">>", 3)))
		{
			prepped[k + i] = ' ';
			prepped[k + i + 1] = s[i];
			prepped[k + i + 2] = ' ';
			k += 2;
			i++;
		}
		else
		{
			prepped[k + i] = s[i];
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
