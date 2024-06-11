/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:32:53 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/11 17:04:43 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_free(char *s)
{
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	dup = (char *)malloc (1 + ft_strlen(s) * sizeof (char));
	if (!dup)
		return (NULL);
	while (s[i] != 0)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	free(s);
	return (dup);
}

int	cmd_is_echo(char *str)
{
	if (ft_strcmp_up_lo(str, "echo"))
		return (0);
	return (1);
}

int	ft_emptyline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		else
			i++;
	}
	return (1);
}

void	fd_routine_no_cmd(t_args *args)
{
	store_original_fds(args);
	redirs_iteration(args->redirects, 0);
	restore_fds(args);
}

void	restore_fds(t_args *args)
{
	dup2(args->original_stdin, STDIN_FILENO);
	close(args->original_stdin);
	dup2(args->original_stdout, STDOUT_FILENO);
	close(args->original_stdout);
}
