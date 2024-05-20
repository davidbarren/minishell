/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:43:48 by plang             #+#    #+#             */
/*   Updated: 2024/05/18 20:28:23 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	how_many_parts(char *str)
{
	int	parts;
	int	i;

	i = 0;
	parts = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) && !ft_isalnum(str[i + 1])
			&& str[i + 1 != '\0'])
			parts++;
		i++;
	}
	return (parts);
}

int	get_part_len(char *str, int i)
{
	int		len;
	char	c;

	len = 0;
	c = 0;
	if (!ft_isalnum(str[i]))
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
void    clean_expand_quotes(char **str)
{
    char    *copy;
    char    *start;
    int        i;
    char    c;

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

/*
int	get_part_len(char *str, int i)
{
	int		len;
	char	c;

	len = 0;
	c = 0;
	if (!ft_isalnum(str[i]))
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
*/

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
	clean_expand_quotes(arg);
	while (arg[i] != '\0')
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
		(*split_cmds) = ft_strjoin(*split_cmds, part_array[j + 1]);
		j++;
	}
}

void	find_expansion(t_env **envs, char **split_cmds)
{
	int		parts;
	char	**part_array;
	int		j;
	int		k;
	int		len;

	j = 0;
	k = 0;
	parts = how_many_parts(*split_cmds);
	part_array = malloc((parts + 1) * sizeof(char *));
	if (!part_array)
		return ;
	while (parts > j)
	{
		len = get_part_len(*split_cmds, k);
		part_array[j] = ft_substr(*split_cmds, k, len);
		k += ft_strlen(part_array[j]);
		j++;
	}
	part_array[j] = 0;
	expand_and_join(envs, split_cmds, part_array);
}

void	ft_expand(char **split_cmds, t_env **envlist)
{
	int	j;

	j = 0;
//	printf("content of split_cmds:%s\n", split_cmds[0]);
	while (split_cmds[j] != NULL)
	{
		if (ft_strchr(split_cmds[j], '$'))
			find_expansion(envlist, &split_cmds[j]);
		j++;
	}
}
