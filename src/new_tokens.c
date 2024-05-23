/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:46:32 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/23 13:38:49 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
void	print_argvalues(t_args *args)
{
	ft_printerror("Value of arglist:%s\n", args->arglist);
	ft_printerror("Value of tokenized_args:%s\n", args->tokenized_args);
	ft_printerror("Value of long_command:%s\n", args->long_command);
	//	ft_printerror("Value of arglist:%s\n", args->arglist);
	//	ft_printerror("Value of arglist:%s\n", args->arglist);
	//	ft_printerror("Value of arglist:%s\n", args->arglist);
	//	ft_printerror("Value of arglist:%s\n", args->arglist);

}

static int	ft_wordlen(char *str)
{
	int	i;

	i = 0;
//	ft_skip_chars(&str, ' ');
	while (str[i] && str[i] != '<' && str[i] != '>')// && str[i] != ' ')
		i++;
	return (i);
}
char *cmd_extraction(char *str)
{
	int	len;
	char *ret;

	len = ft_wordlen(str);
	ret = ft_substring(str, 0, len);
	return (ret);
}
void	case_hdoc(t_args *args)
{
	args->is_hdoc = 1;
	dprintf(2, "In case heredoc");
	return ;

}

void	ft_skip_word(char **str)
{
	while (*str)
	{
		if (ft_isalpha(**str))
			str++;
		else
			break;
	}

}
int	find_next_word(char	*str)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (str[k] == ' ' || str[k] == '<' || str[k] == '>')
		k++;
//	while (str[i + k] != ' ' && str[i + k] != '<' 
//			&& str[i + k] != '>' && str[i + k])
//		i++;
	return (k);
}
void	input_redir_first_token(t_args *args)
{
	char	*temp;
	int	i;

	i = 0;
	temp = args->arglist;
	if (*temp == '<' )
	{
		if (*(temp + 1) == '<')
		{
			args->is_hdoc = 1;
			case_hdoc(args);
		}
		else
		{
			temp += find_next_word(temp);
			i = ft_strlen_mod(temp, ' ');
			args->input = ft_substr(temp, 0, i);
			dprintf(2, "Input file:%s\n", args->input);
			temp += i;
			args->long_command = cmd_extraction(temp);
			temp = ft_strtrim(temp, args->long_command);
			args->tokenized_args = temp;
			printf("value of temp in input:%s\n", temp);
		}
	}
//	dprintf(2, "rest of temp in input:%s\n", temp);
	dprintf(2, "In case input first with input:%s\n", args->input);
}

void	output_redir_first_token(t_args *args)
{
	char	*temp;
	int	i;

	i = 0;
	temp = args->arglist;
	if (*temp == '>' )
	{
		if (*(temp + 1) == '>')
		{
			case_hdoc(args);
		}
		else
		{
			temp += find_next_word(temp);
			i = ft_strlen_mod(temp, ' ');
			args->output = ft_substr(temp, 0, i);
			dprintf(2, "output file:%s\n", args->output);
			temp += i;
//			args->long_command = temp;
//			cmd_extraction(temp);
			args->long_command = cmd_extraction(temp);
			ft_skip_word(&temp);
		}
	}
	dprintf(2, "In case output_first with output:%s\n", args->output);
	dprintf(2, "remainder of temp in output:%s\n", temp);
}

void	condition_redir(t_args	*args)
{
	char	*temp;

	temp = args->arglist;
	ft_skip_chars(&temp, ' ');
	if (*temp == '<') 
		input_redir_first_token(args);
	else if ( *temp == '>')
		output_redir_first_token(args);
	else
	{
		args->long_command = get_cmd_filename_last(temp);
		args->tokenized_args = get_file_filename_last(temp);
	}

}

void	make_tokens(t_args *args)
{
		if (args->redir_count)
			condition_redir(args);
		else
		args->long_command = ft_strdup(args->arglist);
	print_argvalues(args);
}

void	create_redir_list(t_args *args)
{
	args->redirects = ft_calloc (1, sizeof(t_redir));
	if (!args->redirects)
		return ;
}*/
/*
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
			temp->str = ft_strdup(args->tokenized_args);
		}
		temp = temp->next;
	}
}
*/

/*
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




 * Functions to be refactored:
 * clean_arglist and Tokenize_args.
 * Key points:
 * differentiate between input and output redirects
 * consider heredoc
 * consider appending
 * In case of < Makefile cat > new
 * STDIN gets dup'ed to be Makefile
 * STDOUT gets dup'ed to be new
 *
 *For heredoc:
 *work in progress :)
*/
