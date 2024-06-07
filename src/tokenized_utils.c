/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:33:09 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/07 11:22:01 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_extraction(t_args *args, char **tokenlist)
{
	int		i;
	char	*longboi;

	longboi = NULL;
	i = 1;
	while (i < args->token_count)
	{
		if (!redir_check(tokenlist[i]) && !redir_check(tokenlist[i - 1]))
		{
			if (!ft_is_emptystr(tokenlist[i]))
				longboi = ft_strdup(tokenlist[i]);
			i++;
			while (!redir_check(tokenlist[i]))
				longboi = ft_strjoin_sep(longboi, tokenlist[i++], ' ');
		}
		i++;
	}
	if (!longboi || ft_is_emptystr(longboi))
	{
		free(longboi);
		args->long_command = NULL;
		return ;
	}
	args->long_command = ft_strdup_free(longboi);
}

void	find_command(t_args *args, char **tokenlist)
{
	int		i;
	char	*longboi;

	i = 0;
	if (!tokenlist)
		return ;
	if (!redir_check(tokenlist[0]))
	{
		i = 1;
		longboi = ft_strdup(tokenlist[0]);
		while (!redir_check(tokenlist[i]) && i <= args->token_count - 1)
		{
			longboi = ft_strjoin_sep(longboi, tokenlist[i], ' ');
			i++;
		}
		args->long_command = ft_strdup(longboi);
		free(longboi);
	}
	else
		command_extraction(args, tokenlist);
}

int	bad_syntax_post_expansion(char **tokenlist, int *exit_code)
{
	int	k;

	k = 0;
	if (!tokenlist)
		return (1);
	while (tokenlist[k])
	{
		if ((tokenlist[k][0] == '\"' || *tokenlist[k] == '\'')
			&& ((ft_strlen(tokenlist[k]) == 1)))
			k++;
		if (!cmd_is_echo(tokenlist[k]))
		{
			if (!ft_is_emptystr(tokenlist[k]))
				tokenlist[k] = trim_input(tokenlist[k], '\"');
			if (ft_is_emptystr(tokenlist[k]))
				return (emptystr_condition(&tokenlist[k], exit_code));
		}
		k++;
	}
	return (0);
}

int	emptystr_condition(char **tokenlist, int *exit_code)
{
	free(*tokenlist);
	*tokenlist = NULL;
	ft_printerror("Baboonshell: : No such file or directory\n");
	*exit_code = 1;
	return (1);
}

void	free_and_null(char **str)
{
	free(*str);
	*str = NULL;
}
