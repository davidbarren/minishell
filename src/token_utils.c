/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:53 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/20 11:08:49 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(char *str, size_t n, int flag)
{
	size_t	len;
	char	*ret;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < n)
		n = len;
	ret = ft_calloc (n + 2, sizeof(char));
	if (!ret)
		return (NULL);
	while (i <= n)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	if (flag == 1)
		free(str);
	return (ret);
}

int	strlen_delim_double(char *str, char c, char k)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == k)
			break ;
		i++;
	}
	return (i);
}

void	update_redirs(t_args *args)
{
	int		count;
	int		i;
	char	c;

	i = 0;
	count = 0;
	while (args->arglist[i])
	{
		if (args->arglist[i] == '>' || args->arglist[i] == '<')
		{
			c = args->arglist[i];
			i++;
			count++;
			args->has_redir = 1;
			if (args->arglist[i] == c)
			{
				i++;
				args->has_redir = 2;
			}
		}
		else
			i++;
	}
	args->redir_count = count;
}
