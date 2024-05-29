/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:01:28 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/27 16:40:47 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fd_routine_no_cmd(t_args *args)
{
	store_original_fds(args);
	redirs_iteration(args->redirects, 0);
	restore_fds(args);
}
/*
void	condition_hdoc(t_args *args)
{
	char	**tokenlist;
	int		i;
	t_redir	*temp;
	char	*parsed_string;

	parsed_string = prep_tokenizer(args->arglist, args->redir_count);
	tokenlist = ft_quotesplit(parsed_string, ' ');
	args->token_count = ft_arrlen(tokenlist);
}
*/

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
