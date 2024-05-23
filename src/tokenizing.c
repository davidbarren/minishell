/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/22 11:27:47 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_input(char *line, t_input *input)
{
	char	**temp;
	int		i;

	i = 0;
	printf("content of line before expansion:%s\n", line);
	temp = ft_quotesplit(line, '|');
	// int	k = 0;
	// while (temp[k])
	// 	printf("content of temp:%s\n", temp[k++]);
	input->pipe_count = ft_arrlen(temp);
	input->input = ft_calloc(input->pipe_count + 1, sizeof(char *));
	while (temp[i])
	{
		input->input[i] = ft_strdup(temp[i]);
		ft_expand(input->input, input->envlist);
		printf("content of input:%s\n", input->input[i]);
		i++;
	}
	free_2d(temp);
	build_struct(input);
	sanitize_input(input);
	if (input->pipe_count == 1 && input->arg_struct[0]->is_builtin)
		return ;
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
//		if (!ft_strncmp(input->arg_struct[i]->arglist, "<<", 3))
//			input->arg_struct[i]->is_hdoc = 1;
		input->arg_struct[i]->envlist = input->envlist;
		i++;
	}
	i = 0;
}

void	clean_arglist(t_args *args)
{
	char	*delimset;
	char	*word_after;
	char	*temp;
	int		i;

	delimset = NULL;
	i = 0;
	temp = args->arglist;
	ft_skip_chars(&temp, ' ');
	if (args->redir_count)
	{
		if (*temp == '<' || *temp == '>')
		{
			delimset = ft_strndup(temp, 1, 0);
			temp += 1;
			printf("address of temp:%p\n", temp);
			ft_skip_chars(&temp, ' ');
			while (temp[i] != ' ')
				i++;
			word_after = ft_strndup(temp, i, 0);
			temp += i;
			printf("address of temp:%p\n", temp);
			args->tokenized_args = ft_strjoin_flex(delimset, word_after, 3);
			i = strlen_delim_double(temp, '<', '>');
			args->long_command = ft_substr(temp, 0, i);
		}
		else
		{
			args->long_command = get_cmd_filename_last(temp);
			args->tokenized_args = get_file_filename_last(temp);
		}
	}
	else
		args->long_command = ft_strdup(temp);
}

void	tokenize_args(t_args *args)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	temp = args->arglist;
	dprintf(2, "content of arglist in tokenize:%s\n", args->arglist);
	if (args->redir_count)
	{
		args->redirects = ft_calloc(1, sizeof(t_redir *));
		if (!args->redirects)
			return ;
		printf("Temp in tokenize args:%s\n", temp);
		while (*temp)
		{
			len = strlen_delim_double(temp + 1, '>', '<');
			make_redirect_node(args->redirects, temp, len);
			temp += len;
			if (*temp)
				temp += 1;
			i++;
		}
	}
}

void	sanitize_input(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->pipe_count)
	{
		token_splitting(input->arg_struct[i]);
//		make_tokens(input->arg_struct[i]);
//		clean_arglist(input->arg_struct[i]);
//		tokenize_args(input->arg_struct[i]);
//		extract_cmds(input->arg_struct[i]);
//		if (input->arg_struct[i]->redir_count)
//			clean_redir_node(input->arg_struct[i]->redirects,
//				input->arg_struct[i]->long_command);
		prep_and_split_command(input->arg_struct[i]);
		i++;
	}
}
