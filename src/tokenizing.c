/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/25 17:26:34 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_input(char **temp, t_input *input)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		input->input[i] = ft_strdup(temp[i]);
		if (!ft_strnstr(input->input[i], "<<", ft_strlen(input->input[i])))
			ft_expand(input->input, input->envlist, input->exit_status);
		i++;
	}
	free_2d(temp);
}

void	prep_input(char *line, t_input *input)
{
	char	**temp;

	temp = ft_quotesplit(line, '|');
	input->pipe_count = ft_arrlen(temp);
	input->input = ft_calloc(input->pipe_count + 1, sizeof(char *));
	if (!input->input)
		return ;
	copy_input(temp, input);
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
		input->arg_struct[i]->index = i;
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
		token_splitting(input->arg_struct[i], &input->exit_status);
		if (input->arg_struct[i]->redirects)
		{
			store_original_fds(input->arg_struct[i]);
			fetch_and_create_hdoc(input->arg_struct[i]);
			check_g_exit_status(input);
			restore_fds(input->arg_struct[i]);
		}
		prep_and_split_command(input->arg_struct[i], &input->exit_status);
		i++;
	}
}
