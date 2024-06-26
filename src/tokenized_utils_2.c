/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:34:02 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/12 14:50:55 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	alloc_and_make_redirs(char **tokenlist, t_args *args)
{
	args->redirects = ft_calloc(1, sizeof(t_redir *));
	if (!args->redirects)
		return ;
	create_redir_node(tokenlist, args->redirects, args);
}

int	vibecheck_dir(char **str, char *parsedstr)
{
	DIR	*why;
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strnstr(parsedstr, "echo", ft_strlen(parsedstr)))
			break ;
		if (*str[i] == '\"')
			str[i] = trim_input(str[i], '\"');
		why = (opendir(str[i]));
		if (why)
		{
			closedir(why);
			ft_printerror("Baboonshell: %s: Is a Directory\n", str[i]);
			free(parsedstr);
			free_2d(str);
			return (126);
		}
		i++;
	}
	return (0);
}

int	fake_file(char *str)
{
	ft_printerror("🐒:Baboonshell:%s: No such file or directory\n", str);
	return (1);
}

void	cmd_is_dir(char *str)
{
	DIR	*why;

	why = opendir(str);
	if (why)
	{
		closedir(why);
		exit(126);
	}
}
