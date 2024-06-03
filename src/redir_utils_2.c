/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:01:28 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/03 17:26:55 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fd_routine_no_cmd(t_args *args)
{
	store_original_fds(args);
	redirs_iteration(args->redirects, 0);
	restore_fds(args);
}

void	store_original_fds(t_args *args)
{
	args->original_stdin = dup(STDIN_FILENO);
	args->original_stdout = dup(STDOUT_FILENO);
}

void	free_redir_cont(t_redir *redir)
{
	if (redir->str)
		free(redir->str);
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
