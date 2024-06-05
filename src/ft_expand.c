/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:48 by plang             #+#    #+#             */
/*   Updated: 2024/06/05 13:12:42 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	env_count_in_quotes(char *str, char c, int i)
// {
// 	int	env_c;

// 	env_c = 0;
// 	while (str[i] != c && str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] != ' ')
// 			env_c++;
// 		i++;
// 	}
// 	return (env_c);
// }

int	how_many_parts(char *str)
{
	int		parts;
	int		i;
	char	temp;

	i = 0;
	parts = 0;
	temp = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) && !ft_isalnum(str[i + 1])
			&& str[i + 1 != '\0'] && str[i + 1] != '_')
			parts++;
		else if (str[i] == ' ' )
		{
			while (str[i] == ' ' && str[i + 1] != '\0')
				i++;
			parts++;
		}
		if (str[i] == '"' || str[i] == '\'')
		{
			temp = str[i];
			i++;
			while (str[i] != temp && str[i + 1] != '\0')
				i++;
			parts++;
		}
		if (str[i] == '>' || str[i] == '<')
		{
			temp = str[i];
			i++;
			while (str[i] != temp && str[i + 1] != '\0')
				i++;
			parts++;
		}
		if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			parts++;
		if (str[i] == '=' || str[i] == '?')
			parts++;
		i++;
	}
	return (parts + 1);
}

//added parts++ if $, we need to run tests, also str[i] == 
//'=', len and parts are so so but works for now. need to fix if:s

int	get_part_len(char *str, int i)
{
	int		len;
	char	c;

	len = 0;
	c = 0;
	if (str[i] == ' ')
	{
		while (str[i] == ' ')
		{
			i++;
			len++;
		}
		return (len);
	}
	if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
	{
		i++;
		return (1);
	}
	if (!ft_isalnum(str[i]) && str[i] != 0)
	{
		if (str[i] == '$')
		{
			i++;
			len++;
		}
		if (str[i] == '"' || str[i] == '\'')
			c = str[i];
		i++;
		len++;
	}
	while (str[i] != '\0')
	{
		if (!c && !ft_isalnum(str[i]) && str[i] != '_' && str[i] != '?')
			return (len);
		if (c && str[i] == c)
			return (len + 1);
		i++;
		len++;
	}
	return (len);
}

void	clean_expand_quotes(char **str)
{
	char	*copy;
	char	*start;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = 0;
	copy = ft_strdup(*str);
	if (!copy)
		return ;
	start = copy;
	while (copy[j])
	{
		if (copy[j] == '"' || copy[j] == '\'')
		{
			c = copy[j];
			j++;
			while (copy[j] != c && copy[j])
			{
				(*str)[i++] = copy[j];
				j++;
			}
		}
		else if (copy[j] != '"' && copy[j] != '\'')
			(*str)[i++] = copy[j];
		j++;
	}
	(*str)[i] = '\0';
	free(start);
}

char	*expand_key(t_env *node)
{
	char	*key_value;

	key_value = ft_strdup(node->info);
	return (key_value);
}

void	get_len_for_key(char *arg, int *i, int *len)
{
	if (arg[*i] == '?')
	{
		(*len) += 1;
		(*i) += 1;
		return ;
	}
	while (arg[*i] != '\0' && ft_isalpha(arg[*i]))
	{
		(*len) += 1;
		(*i) += 1;
		if (arg[*i] == '_')
		{
			(*len) += 1;
			(*i) += 1;
		}
	}
}
// add check for len for ?, move while loop bellow to own
// function and make a function that we go in to if check
// is a ?. then we set them the same way and return check
// add the int exit_status in the function calls starting
// from ft_export!
void	expand_qm(char **check, char **rest, int es)
{
	//free(check);
	*check = ft_itoa(es);
	*check = ft_strjoin_flex(*check, *rest, 3);
	return ;
}

char	*is_expansion_valid(t_env **envs, char *arg, int i, int es)
{
	char	*check;
	int		lenstart[2];
	t_env	*temp;
	char	*rest;

	lenstart[0] = 0;
	lenstart[1] = i;
	temp = *envs;
	get_len_for_key(arg, &i, &lenstart[0]);
	check = ft_substr(arg, lenstart[1], lenstart[0]);
	printf("check: %s\n", check);
	rest = ft_substr(arg, i, (ft_strlen(arg) - i));
	printf("rest: %s\n", rest);
	printf("arg: %s\n", arg);
	if (check[0] == '?')
	{
		printf("hello\n");
		expand_qm(&check, &rest, es);
		return (check);
	}
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->title, check))
		{
			free(check);
			check = expand_key(temp);
			check = ft_strjoin_flex(check, rest, 3);
			return (check);
		}
		temp = temp->next;
	}
	free(check);
	check = rest;
	return (check);
}

int	get_qflag(char *arg)
{
	int	flag;
	int	j;

	j = 0;
	flag = 0;
	while (arg[j] != '\0')
	{
		if (arg[j] == '\'')
		{
			flag = 2;
			break ;
		}
		else if (arg[j] == '"')
		{
			flag = 1;
			break ;
		}
		j++;
	}
	return (flag);
}

char	*get_beginning(char *str)
{
	int		i;
	char	*beginning;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (str[i + 1] == ' ')
		while (str[i] == ' ')
			i++;
	beginning = ft_substr(str, 0, i);
	if (!beginning)
		return (NULL);
	return (beginning);
}

void	expand_rest(t_env **envs, char **arg, int *i, int es)//, int *dq
{
	while ((*arg)[*i] != '\0')
	{
		if ((*arg)[*i] == '$')// && *dq > 0
		{
			expand_check_arguments(envs, arg, es);//, dq
			//(*dq) -= 1;
		}
		(*i) += 1;
	}
}

void	assign_expanded(char **arg, char *expanded, char *beginning)
{
	if (!expanded)
		*arg = ft_strdup("");
	else
		*arg = expanded;
	if (beginning)
		*arg = ft_strjoin_flex(beginning, expanded, 3);
}

void	expand_check_arguments(t_env **envs, char **arg, int es)//, int *dq
{
	int			i;
	char		*expanded;
	int			qflag;
	char		*beginning;

	i = 0;
	qflag = get_qflag(*arg);
	beginning = 0;
	if ((*arg)[0] != '$' && ft_strchr((*arg), '$') && qflag < 2)
		beginning = get_beginning((*arg));
	while ((*arg)[i] != '\0')
	{
		if ((*arg)[i] == '$' && qflag < 2 && (*arg)[i + 1] != '\0')
		{
			i++;
			expanded = is_expansion_valid(envs, *arg, i, es);
			free(*arg);
			assign_expanded(arg, expanded, beginning);
			if (ft_strchr((*arg), '$') && qflag < 2) //&& (*dq) > 0
				expand_rest(envs, arg, &i, es);// dq,
			break ;
		}
		i++;
	}
}

void	expand_and_join(t_env **envs, char **split_cmds, char **part_array, int es)
{
	int	j;
	// int	eflag;
	// int	dq;

	j = 0;
	// eflag = 0;
	while (part_array[j] != NULL)
	{
		// if ((ft_strcmp_up_lo("echo", part_array[0]) == 0))
		// 	eflag = 1;
		// dq = quote_count(part_array[j], '$');
		expand_check_arguments(envs, &part_array[j], es);//,&dq
		j++;
	}
	j = 0;
	free(*split_cmds);
	*split_cmds = part_array[j];
	while (part_array[j + 1] != NULL)
	{
		(*split_cmds) = ft_strjoin_flex(*split_cmds, part_array[j + 1], 3);
		j++;
	}
	// if (eflag == 0)
	// 	clean_expand_quotes(split_cmds);
	free(part_array);
}

void	find_expansion(t_env **envs, char **split_cmds, int es)
{
	int		parts;
	char	**part_array;
	int		j;
	int		start;
	int		len;

	j = 0;
	start = 0;
	parts = how_many_parts(*split_cmds);
	printf("parts: %d\n", parts);
	part_array = malloc((parts + 1) * sizeof(char *));
	if (!part_array)
		return ;
	while (parts > j)
	{
		len = get_part_len(*split_cmds, start);
		printf("len: %d\n", len);
		part_array[j] = ft_substr(*split_cmds, start, len);
		printf("part of str: %s\n", part_array[j]);
		start += ft_strlen(part_array[j]);
		j++;
	}
	part_array[j] = 0;
	expand_and_join(envs, split_cmds, part_array, es);
}

void	ft_expand(char **split_cmds, t_env **envlist, int es)
{
	int	j;

	j = 0;
	while (split_cmds[j] != NULL)
	{
		if (ft_strchr(split_cmds[j], '$'))
			find_expansion(envlist, &split_cmds[j], es);
		j++;
	}
}
