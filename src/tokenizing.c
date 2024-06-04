/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/04 15:30:56 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_input(char *line, t_input *input)
{
	char	**temp;
	int		i;

	i = 0;
	temp = ft_quotesplit(line, '|');
	input->pipe_count = ft_arrlen(temp);
	input->input = ft_calloc(input->pipe_count + 1, sizeof(char *));
	while (temp[i])
	{
		input->input[i] = ft_strdup(temp[i]);
		if (!ft_strnstr(input->input[i], "<<", ft_strlen(input->input[i]))) // temp fix with strnstr in case someone passes << as arg for cmd
			ft_expand(input->input, input->envlist);
		else
			dprintf(2, "hdoc found in prep input and shit not expanded\n");
		i++;
	}
	free_2d(temp);
	build_struct(input);
	tokenize_input(input);
	free_2d(input->input);
	input->input = NULL;
	if (input->pipe_count == 1 && input->arg_struct[0]->is_builtin)
		return ;
	if (input->pipe_count == 1 && !input->arg_struct[0]->long_command)
	{
		fd_routine_no_cmd(input->arg_struct[0]);
		return ;
	}
	prep_pids(input);
}

void	build_struct(t_input *input)
{
	int	i;

	i = 0;
	input->arg_struct = ft_calloc ((input->pipe_count), sizeof(t_args *));
	if (!input->arg_struct)
		return ;
	while (i < input->pipe_count)
	{
		input->arg_struct[i] = ft_calloc (1, sizeof (t_args));
		if (!input->arg_struct[i])
			return ;
		input->arg_struct[i]->pipecount = input->pipe_count;
		input->arg_struct[i]->is_builtin = 0;
		input->arg_struct[i]->arglist = ft_strdup(input->input[i]);
		if (!input->arg_struct[i]->arglist)
			return ;
		update_redirs(input->arg_struct[i]);
		input->arg_struct[i]->envlist = input->envlist;
		i++;
	}
	i = 0;
}

void	tokenize_input(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->pipe_count)
	{
		// dprintf(2, "Hdoc status of struct at index:%d ... status:%d\n", i, input->arg_struct[i]->is_hdoc);
		if (input->arg_struct[i]->is_hdoc)
			dprintf(2," we out here with hdoc motherfucker!\n");
//			 condition_hdoc(input->arg_struct[i]);
//		}
//		else
		token_splitting(input->arg_struct[i]);
		prep_and_split_command(input->arg_struct[i]);
		i++;
	}
}
