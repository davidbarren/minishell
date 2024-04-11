/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/11 19:21:34 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_redir *get_final_node(t_redir *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	prep_input(char *input, t_args *args)
{

	args->arglist = ft_quotesplit(input, '|'); 
	int i = 0;
	while (args->arglist[i])
		printf("Elements of split array:%s\n", args->arglist[i++]);
//	scan_input(input, args);
//	scan input function segfaults atm, fix it!
}

void	scan_input(char *input, t_args *args)
{
	int i;
	int push;
	char c;
	char *newin;

	while (*input)
	{
		if (*input == '>' || *input == '<')
		{
			c = *input;
			push = strlen_delim(input, 'c');
			printf("%c\n", c);
			newin = ft_substr(input, 0, push);
			make_redir_node(newin, args->redirects);
			input += push;
		}
		input++;
	}
	i = 0;
	while (args->redirects[i])
		printf("From scan input: %s\n", args->redirects[i++]->str);
}
void	make_redir_node(char *input, t_redir **redir)
{
	t_redir	*last_node;
	t_redir	*new_node;
	t_redir	*temp;

	temp = *redir;
	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return ;
	new_node->str = input;
	new_node->next = NULL;
	if (!*redir)
		*redir = new_node;
	else
	{
		last_node = get_final_node(*redir);
		last_node->next = new_node;
	}
}

int strlen_delim(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
