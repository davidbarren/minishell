/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:48 by plang             #+#    #+#             */
/*   Updated: 2024/05/23 11:44:20 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			&& str[i + 1 != '\0'])
			parts++;
		else if (str[i] == ' ')
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
		i++;
	}
	return (parts);
}

int	get_part_len(char *str, int i)//, int *wordstart
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
	// while (str[i] == ' ')
	// {
	// 	i++;
	// 	(*wordstart)++;
	// }
	if (!ft_isalnum(str[i]) && str[i] != 0)
	{
		if (str[i] == '"' || str[i] == '\'')
			c = str[i];
		i++;
		len++;
	}
	while (str[i] != '\0')
	{
		if (!c && !ft_isalnum(str[i]))
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
	char	c;

	i = 0;
	c = 0;
	copy = ft_strdup(*str);
	if (!copy)
		return ;
	start = copy;
	while (*copy)
	{
		if (*copy == '"' || *copy == '\'')
		{
			c = *copy;
			copy++;
			while (*copy != c && *copy)
			{
				(*str)[i++] = *copy;
				copy++;
			}
		}
		else if (*copy != '"' && *copy != '\'')
			(*str)[i++] = *copy;
		copy++;
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

char	*is_expansion_valid(t_env **envs, char *arg, int i)
{
	char	*check;
	int		len;
	int		start;
	t_env	*temp;

	len = 0;
	start = i;
	temp = *envs;
	while (arg[i] != '\0' && ft_isalpha(arg[i]))
	{
		len++;
		i++;
	}
	check = ft_substr(arg, start, len);
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->title, check))
		{
			free(check);
			check = expand_key(temp);
			return (check);
		}
		temp = temp->next;
	}
	return (NULL);
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

void	expand_check_arguments(t_env **envs, char **arg)
{
	int		i;
	char	*expanded;
	int		qflag;
	int		j;

	i = 0;
	j = 0;
	qflag = get_qflag(*arg);
	if (ft_strchr(*arg, '$'))
		clean_expand_quotes(arg);
	while ((*arg)[i] != '\0')
	{
		if ((*arg)[i] == '$' && qflag < 2)
		{
			i++;
			expanded = is_expansion_valid(envs, *arg, i);
			free(*arg);
			if (!expanded)
				*arg = ft_strdup("");// = NULL;
			else
				*arg = expanded;
			break ;
		}
		i++;
	}
}
// but NULL breaks expansion of multiple env variables 
// EMPTY STRING BREAKS ERROR MSGS

void	expand_and_join(t_env **envs, char **split_cmds, char **part_array)
{
	int	j;

	j = 0;
	while (part_array[j] != NULL)
	{
		expand_check_arguments(envs, &part_array[j]);
		j++;
	}
	j = 0;
	free(*split_cmds);
	*split_cmds = part_array[j];
	while (part_array[j + 1] != NULL)
	{
		clean_expand_quotes(split_cmds);
		(*split_cmds) = ft_strjoin(*split_cmds, part_array[j + 1]);
		j++;
	}
}
//ft_strjoin_flex(on part_array);

void	find_expansion(t_env **envs, char **split_cmds)
{
	int		parts;
	char	**part_array;
	int		j;
	int		k; //start
	int		len;

	j = 0;
	k = 0;
	dprintf(2, "content of string in find_expand %s\n", *split_cmds);
	parts = how_many_parts(*split_cmds);
	dprintf(2, "parts in string:%d\n", parts);
	part_array = malloc((parts + 1) * sizeof(char *));
	if (!part_array)
		return ;
	while (parts > j)
	{
		dprintf(2, "start position of len:%d\n", k);
		len = get_part_len(*split_cmds, k);//, &k
		dprintf(2, "len of part:%d\n", len);
		part_array[j] = ft_substr(*split_cmds, k, len);
		dprintf(2, "content of string in part_array =%s=\n", part_array[j]);
		k += ft_strlen(part_array[j]);
		dprintf(2, "k after strdup:%d\n", k);
		j++;
	}
	part_array[j] = 0;
	expand_and_join(envs, split_cmds, part_array);
}

void	ft_expand(char **split_cmds, t_env **envlist)
{
	int	j;

	j = 0;
	dprintf(2, "address of split cmds head:%p\n", split_cmds);
	while (split_cmds[j] != NULL)
	{
		dprintf(2, "address of string in ft_expand at index:%d %p\n", j, split_cmds[j]);
		dprintf(2, "content of string in ft_expand at index:%d %s\n", j, split_cmds[j]);
		if (ft_strchr(split_cmds[j], '$'))
			find_expansion(envlist, &split_cmds[j]);
		j++;
	}
}
