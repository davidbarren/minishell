/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/07 16:35:14 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_input(char *line, t_input *input)
{
	char	**temp;
	int		i;

	i = 0;
//	printf("Line from readline:%s\n", line);
	temp = ft_quotesplit(line, '|');
//	printf("quotesplit index 0 in prepinput:%s\n", temp[0]);
	input->pipe_count = ft_arrlen(temp);
	input->input = ft_calloc(input->pipe_count + 1, sizeof(char *));
	while (temp[i])
	{
		input->input[i] = ft_strdup(temp[i]);
		i++;
	}
	free_2d(temp);
	build_struct(input);
	i = 0;
//	printf("pipecount in input:%d\n", input->pipe_count);
	while (i < input->pipe_count)
	{
//		printf("Iteration number:%d\n", i);
		clean_arglist(input->arg_struct[i]);
		tokenize_args(input->arg_struct[i]);
		extract_cmds(input->arg_struct[i]);
		if (input->arg_struct[i]->redir_count)
		{
			clean_redir_node(input->arg_struct[i]->redirects,
					input->arg_struct[i]->long_command);
			file_opening(*input->arg_struct[i]->redirects, input->arg_struct[i]);
//			redir_fd_modifying(input->arg_struct[i]->redirects);
		}
//		printf("iteration number:%d with pipecount:%d\n", i, input->pipe_count);
		i++;
//		prep_child_command(input->arg_struct[i++]);
	}
		prep_pids(input);
}

void	build_struct(t_input *input)
{
	int	i;

	i = 0;
	input->arg_struct = ft_calloc ((input->pipe_count) , sizeof(t_args *));
	if (!input->arg_struct)
		return ;
	while (i < input->pipe_count)
	{
		input->arg_struct[i] = malloc (sizeof (t_args));
		if (!input->arg_struct[i])
			return ;
		input->arg_struct[i]->arglist = ft_strdup(input->input[i]);
		if (!input->arg_struct[i]->arglist)
			return ;
		update_redirs(input->arg_struct[i]);
		if (!ft_strncmp(input->arg_struct[i]->arglist, "<<", 3))
			input->arg_struct[i]->is_hdoc = 1;
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

//	printf("address of args struct:%p\n", args);
	delimset = NULL;
	i = 0;
	temp = args->arglist;
	ft_skip_chars(&temp, ' ');
//	printf("arglist before pointer arithmetic:%p\n", args->arglist);
	if (args->redir_count)
	{
		if (*temp == '<' || *temp == '>')
		{
			delimset = ft_strndup(temp, 1, 0);
			temp += 1;
			ft_skip_chars(&temp, ' ');
			while (temp[i] != ' ')
				i++;
			word_after = ft_strndup(temp, i, 0);
			temp += i;
			args->tokenized_args = ft_strjoin_flex(delimset, word_after, 3);
			i = strlen_delim_double(temp, '<', '>');
			args->long_command = ft_substr(temp, 0, i);
		}
		else
		{
//			printf("Temp before going into filename last:%p\n", temp);
			args->long_command = get_cmd_filename_last(temp);
			args->tokenized_args = get_file_filename_last(temp);
		}
	}
	else
		args->long_command = ft_strdup(temp);
//	printf("long_command:%s\n", args->long_command);
}

void	tokenize_args(t_args *args)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	temp = args->arglist;
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
