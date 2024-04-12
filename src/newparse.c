/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/12 16:42:51 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_args *get_final_node(t_args *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	prep_input(char *input, t_args **args)
{
	int i;
	t_args *temp;
	i = 0;
	make_arg_node(input, args);
	temp = *args;
//	args->arglist = ft_quotesplit(input, '|');
	while (temp)
	{
		while (temp->arglist[i])
			printf("Elements of split array:%s\n", temp->arglist[i++]);
		temp = temp->next;
		i = 0;
	}
	printf("input:%s\n", input);
}
/*
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
*/
void	make_arg_node(char *input, t_args **args)
{
	t_args	*last_node;
	t_args	*new_node;

	new_node = malloc(sizeof(t_args));
	if (!new_node)
		return ;
	new_node->arglist = ft_quotesplit(input, '|');
	if (!new_node->arglist)
		return ;
	new_node->next = NULL;
	if (!*args)
		*args= new_node;
	else
	{
		last_node = get_final_node(*args);
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
