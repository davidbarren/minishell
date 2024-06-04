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

void	copy_input(char **temp, t_input *input)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		input->input[i] = ft_strdup(temp[i]);
		if (!ft_strnstr(input->input[i], "<<", ft_strlen(input->input[i])))
			ft_expand(input->input, input->envlist);
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
		token_splitting(input->arg_struct[i]);
		if (input->arg_struct[i]->redirects)
		{
			store_original_fds(input->arg_struct[i]);
			fetch_and_create_hdoc(input->arg_struct[i]);
			restore_fds(input->arg_struct[i]);
		}
		prep_and_split_command(input->arg_struct[i]);
		i++;
	}
}

void	print_struct_debug(t_args*args)
{
	int k;

	k = 0;
	printf("address of arglist:%p\n", args->arglist);
	printf("address of split_cmds head:%p\n", args->split_cmds);
	while (args->split_cmds[k])
		printf("address of split_cmds :%p\n", args->split_cmds[k++]);
	printf("address of tokenized_args:%p\n", args->tokenized_args);
	printf("address of long_command:%p\n", args->long_command);
	k = 0;
	printf("address of split_path head:%p\n", args->split_path);
	while (args->split_path[k])
		printf("address of split_path:%p\n", args->split_path[k++]);
	printf("address of execpath:%p\n", args->execpath);
	printf("content of execpath:%s\n", args->execpath);
	printf("address of envcpy:%p\n", args->envcpy);
	k = 0;
	while (args->envcpy[k])
		printf("address of envcpy:%p\n", args->envcpy[k++]);
	printf("address of input:%p\n", args->input);
	printf("address of output:%p\n", args->output);

}
