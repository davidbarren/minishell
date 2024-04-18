/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:53 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/18 17:39:00 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(char *str, size_t n)
{
	size_t len;
	char	*ret;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len <  n)
		n = len;
	ret = malloc (n + 2 * sizeof(char));
	if (!ret)
		return (NULL);
	while(i <= n)
	{
		ret[i] = str[i];
			i++;
	}
	ret[i] = 0;
	return (ret);
}

int		ft_is_redirect(char *str)
{
	char *list[5];
	int i;
	int result;

	i = 0;
	list[0] = "<";
	list[1] = "<<";
	list[2] = ">";
	list[3] = ">>";
	list[4] = NULL;
	while (i < 4)
	{
		result = ft_strncmp(str, list[i++], 3);
		if (!result)
			return (1);
	}
	return (0);

}

int strlen_delim_double(char *str, char c, char k)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == k)
			break;
		i++;
	}
	return (i);
}

