/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:08:54 by plang             #+#    #+#             */
/*   Updated: 2024/06/06 18:48:21 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	space_parts(char *str, int *i, int *parts)
{
	while (str[*i] == ' ' && str[*i + 1] != '\0')
		(*i) += 1;
	(*parts) += 1;
}

void	quote_redir_parts(char *str, int *i, int *parts, char *temp)
{
	*temp = str[*i];
	(*i) += 1;
	while (str[*i] != *temp && str[*i + 1] != '\0')
		(*i) += 1;
	(*parts) += 1;
}

void	redir_parts(char *str, int *i, int *parts, char *temp)
{
	*temp = str[*i];
	(*i) += 1;
	if (str[*i] == *temp)
		while (str[*i] != *temp && str[*i + 1] != '\0')
			(*i) += 1;
	else
		while (str[*i] == *temp && str[*i + 1] != '\0')
			(*i) += 1;
	(*parts) += 1;
}

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
			space_parts(str, &i, &parts);
		if (str[i] == '"' || str[i] == '\'')
			quote_redir_parts(str, &i, &parts, &temp);
		if (str[i] == '>' || str[i] == '<')
			redir_parts(str, &i, &parts, &temp);
		if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			parts++;
		if (str[i] == '=' || str[i] == '?')
			parts++;
		i++;
	}
	return (parts + 1);
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

void	expand_rest(t_env **envs, char **arg, int *i, int es)
{
	while ((*arg)[*i] != '\0')
	{
		if ((*arg)[*i] == '$')
		{
			expand_check_arguments(envs, arg, es);
		}
		(*i) += 1;
	}
}
