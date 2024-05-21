/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:44:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/21 20:52:02 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_validation(char *element)
{
	char	*tokens[5];
	int		status;

	status = 0;
	tokens[0] = "<";
	tokens[1] = "<<";
	tokens[2] = ">";
	tokens[3] = ">>";
	tokens[4] = 0;
	if (!element)
		return (-1);
	if (!ft_strcmp(tokens[0], element))
		status = (1);
	else if (!ft_strcmp(tokens[1], element))
		status = (2);
	else if (!ft_strcmp(tokens[2], element))
		status = (3);
	else if (!ft_strcmp(tokens[3], element))
		status = (4);
	return (status);
}

void	create_redir_node(char **tokenlist, t_redir **redirs, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->token_count - 1)
	{
		if (redir_validation(tokenlist[i]) == 1)
			make_redirect_node(redirs, tokenlist[i + 1], 1);
		else if (redir_validation(tokenlist[i]) == 2)
			make_redirect_node(redirs, tokenlist[i + 1], 2);
		else if (redir_validation(tokenlist[i]) == 3)
			make_redirect_node(redirs, tokenlist[i + 1], 3);
		else if (redir_validation(tokenlist[i]) == 3)
			make_redirect_node(redirs, tokenlist[i + 1], 3);
		i++;
	}
}

void	make_redirect_node(t_redir **redir, char *str, int type)
{
	t_redir	*new;
	t_redir	*last;

	new = ft_calloc (1, sizeof(t_redir));
	if (!new)
		return ;
	new->next = NULL;
	new->redir_type = type;
	new->str = ft_strdup(str);
	if (!new->str)
		return ;
	if (!*redir)
		*redir = new;
	else
	{
		last = get_last_redir(*redir);
		last->next = new;
	}
}

void	command_extraction(t_args *args, char **tokenlist)
{
	int		i;
	char	*longboi;

	i = 1;
	while (i < args->token_count - 1)
	{
		if (!redir_validation(tokenlist[i]) && !redir_validation(tokenlist[i - 1]))
		{
			longboi = ft_strdup(tokenlist[i]);
			i++;
			while (!redir_validation(tokenlist[i]))
			{
				longboi = ft_strjoin_sep(longboi, tokenlist[i], ' ');
				i++;
			}
		}
		i++;
	}
	args->long_command = ft_strdup(longboi);
}

void	find_command(t_args *args, char **tokenlist)
{
	int		i;
	char	*longboi;

	i = 0;
	if (!tokenlist)
		return ;
	if (!redir_validation(tokenlist[0]))
	{
		i = 1;
		longboi = ft_strdup(tokenlist[0]);
		while (!redir_validation(tokenlist[i]) && i <= args->token_count - 1)
		{
			printf("joining strings:%s and :%s\n", longboi, tokenlist[i]);
			longboi = ft_strjoin_sep(longboi, tokenlist[i], ' ');
			i++;
		}
		args->long_command = ft_strdup(longboi);
	}
	else
		command_extraction(args, tokenlist);
	printf("long command:%s\n", args->long_command);
}

void	token_splitting(t_args *args)
{
	char	**tokenlist;
	int		i;
	t_redir	*temp;

	i = 0;
	tokenlist = ft_quotesplit(args->arglist, ' ');
	args->token_count = ft_arrlen(tokenlist);
	printf("token count:%d\n", args->token_count);
	printf("content of tokenlist at index 0 :%s\n", tokenlist[0]);
	printf("value of redir count:%d\n", args->redir_count);
	int	k = 0;
	while (tokenlist[k])
		printf("Value of tokenlist:%s\n", tokenlist[k++]);
	if (args->redir_count)
	{
		args->redirects = ft_calloc(1, sizeof(t_redir *));
		if (!args->redirects)
			return ;
		create_redir_node(tokenlist, args->redirects, args);
		temp = *args->redirects;
		while (temp)
		{
			printf("filename in temp:%s\n withtype:%d\n",
				temp->str, temp->redir_type);
			temp = temp->next;
		}
	}
	find_command(args, tokenlist);
	free_2d(tokenlist);
}
