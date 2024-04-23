/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:32:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/23 11:25:05 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 
 * remember to add condition if it's just one word it should be a cmd
 * don't be a baboon!
 * */

void	prep_input(char *line, t_input *input)
{
	char	**temp;
	int		i;
	t_redir *iterator;

	i = 0;
	temp = ft_quotesplit(line, '|');
	input->pipe_count = ft_arrlen(temp);
	input->input = ft_calloc(input->pipe_count + 1, sizeof(char *));
	while (temp[i])
	{
		input->input[i] = trim_input(temp[i], ' ');
		i++;
	}
	free_2d(temp);
	build_struct(input);
	i = 0;
	while (i < input->pipe_count)
	{
			clean_arglist(input->arg_struct[i]);
		tokenize_args(input->arg_struct[i]);
		extract_cmds(input->arg_struct[i]);
		if (input->arg_struct[i]->redir_count)
		{
			iterator = *(input->arg_struct[i]->redirects);
			while (iterator)
			{
				printf("Info in the arg_struct:%s\n", iterator->str);
				iterator = iterator->next;
			}
		}
		printf("Commands to run: %s\n", input->arg_struct[i++]->long_command);
	}
}

void	build_struct(t_input *input)
{
	int	i;

	i = 0;
	input->arg_struct = malloc (input->pipe_count * sizeof(t_args *));
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
		i++;
	}
	i = 0;
}

int quotes_num(char *line)
{
	int i;
	int	singlect;
	int doublect;

	if (!line)
		return (0);
	i = 0;
	singlect = 0;
	doublect = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			singlect++;
		if (line[i] == '\"')
			doublect++;
		i++;
	}
	if ((singlect % 2) || (doublect % 2))
		return (0);
	return (1);
}
 
void	clean_arglist(t_args *args)
{
	char	*delimset;
	char	*word_after;
	char	*temp;
	int		i;
//	int		ducklen;

//	printf("arglist at start of clean:%s\n", args->arglist);
	i = 0;
	temp = args->arglist;
	ft_skip_chars(&temp, ' ');
	if (args->redir_count)
	{
		if (*temp == '<' || *temp == '>') 
		{
			delimset = ft_strndup(temp,1);
			temp += 1;
		}
		ft_skip_chars(&temp, ' ');
		while (temp[i] != ' ')
			i++;
		word_after = ft_strndup(temp, i);
		temp += i;
		args->tokenized_args = ft_strjoin_flex(delimset, word_after, 3);
		//	printf("cleaned arglist:%s\n", args->tokenized_args);
		i = strlen_delim_double(temp, '<', '>');
		args->long_command = ft_substr(temp, 0, i);
	}
	else
		args->long_command = ft_strdup(temp);
//	printf("longboi:%s\n", args->long_command);

	

/* the logic so far is:
  * delimiters go in delimset, need to determine if << or >
  * regardless of case of double or single delims:
  * strndup the delims
  * skip the whitespace if any
  * strndup the word following the delimset
  * ft_strjoin_flex both and free the remainder
  * then check for further delims ands go agane
  * after there are no more delim - word sets
  * rest of the input is a cmd or an argument for the cmd
  * those will then get split and sent to execve, need to maybe trim 
  * quotes from those but that should not be an issue 
  *  
*/ 
}


void	tokenize_args(t_args *args)
{
	char	*temp;
	int		len;

	temp = args->arglist;
//	printf("Inside tokenize args: %s\n", args->arglist);
	if (args->redir_count)
	{
		args->redirects = ft_calloc(1, sizeof(t_redir *));
		if (!args->redirects)
			return ;

		int i = 0;
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

static t_redir	*get_last_redir(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (temp->next)
		temp = temp->next;
	return (temp);
}


void	make_redirect_node (t_redir **redir, char *str, int len)
{
	t_redir	*new;
	t_redir	*last;

	new = calloc (1, sizeof(t_redir));
	if (!new)
		return ;
	new->index = 0;
	new->next = NULL;
	new->str = ft_strndup(str, len);
	if (!new->str)
		return ;
	if (!*redir)
		*redir = new;
	else
	{
		last = get_last_redir(*redir);
		last->next = new;
		new->index = last->index + 1;
	}
}
int		ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}


void	extract_cmds(t_args *args)
{
	
	t_redir	*temp;

	if (!args->redir_count)
		return ;
	temp = *(args->redirects);
	while (temp)
	{
		if (ft_strnstr(temp->str, args->long_command, ft_strlen(temp->str)))
		{
			free (temp->str);
			temp->str = ft_strdup(args->tokenized_args);
		}
		temp = temp->next;
	}
}

