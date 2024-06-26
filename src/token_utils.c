/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:53 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/12 13:19:23 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_hdoc_status(t_args *args)
{
	if (args->arglist)
	{
		if (ft_strnstr(args->arglist, "<<", ft_strlen(args->arglist)))
		{
			args->is_hdoc = 1;
		}
	}
}

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

void	update_redirs(t_args *args)
{
	int		count;
	int		i;
	char	c;

	i = 0;
	count = 0;
	while (args->arglist[i])
	{
		if (args->arglist[i] == '\'' || args->arglist[i] == '\"')
			update_redir_quotehelper(args, &i, c);
		if (args->arglist[i] == '>' || args->arglist[i] == '<')
		{
			c = args->arglist[i];
			i++;
			count++;
			if (args->arglist[i] == c)
			{
				i++;
			}
		}
		else if (args->arglist[i])
			i++;
	}
	args->redir_count = count;
	update_hdoc_status(args);
}

void	update_redir_quotehelper(t_args *args, int *i, char c)
{
	c = args->arglist[*i];
	*i += 1;
	while (args->arglist[*i] != c && args->arglist[*i])
		*i += 1;
	if (args->arglist[*i] && args->arglist[*i] == c)
		*i += 1;
}
