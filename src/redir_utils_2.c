/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:01:28 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/04 17:23:27 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	store_original_fds(t_args *args)
{
	args->original_stdin = dup(STDIN_FILENO);
	args->original_stdout = dup(STDOUT_FILENO);
}

void	free_redir_cont(t_redir *redir)
{
	if (redir->str)
		free(redir->str);
	if (redir->hdoc_title)
		free(redir->hdoc_title);
}

void	free_redirs(t_redir **redirs)
{
	t_redir	*next;

	if (!*redirs)
		return ;
	next = *redirs;
	while (next)
	{
		next = next->next;
		free_redir_cont(*redirs);
		free (*redirs);
		*redirs = next;
	}
	free(redirs);
}

t_redir	*get_last_hdoc(t_redir **redirs)
{
	t_redir	*temp;
	t_redir	*target;

	temp = *redirs;
	target = NULL;
	while (temp)
	{
		if (temp->redir_type == 2)
			target = temp;
		temp = temp->next;
	}
	return (target);
}

void	fetch_and_create_hdoc(t_args *args)
{
	t_redir	*hdoc;

	hdoc = get_last_hdoc(args->redirects);
	dprintf(2, "address of hdoc node:%p\n", hdoc);
	if (!hdoc)
		return ;
	create_hdoc(hdoc);
}
