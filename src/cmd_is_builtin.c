/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:03:25 by plang             #+#    #+#             */
/*   Updated: 2024/05/21 16:54:37 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_strcmp_up_lo(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else if (s1[i] - s2[i] == 32 || s1[i] - s2[i] == -32)
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}

int	cmd_is_builtin(t_env **envs, char **args)
{
	if (ft_strcmp_up_lo("pwd", args[0]) == 0)
		return (ft_pwd());
	if (ft_strcmp_up_lo("echo", args[0]) == 0)
		return (ft_echo(args));
	if (ft_strcmp_up_lo("env", args[0]) == 0)
		return (ft_env(envs));
	if (ft_strncmp("export", args[0], ft_strlen(args[0])) == 0)
		return (ft_export(envs, args));
	if (ft_strncmp("unset", args[0], ft_strlen(args[0])) == 0)
		return (ft_unset(envs, args));
	if (ft_strncmp("cd", args[0], ft_strlen(args[0])) == 0)
		return (ft_cd(envs, args));
	return (1);
}

int	flag_for_builtin(char **args)
{
	// int k = 0;
	// while (args[k])
	// {
	// 	dprintf(2,"content of args:%s\n", args[k]); //remove
	// 	k++;
	// }
	if (!*args)
		return (0);
	// if (ft_is_emptystr(args[0]))
		// return (0);
	if (ft_strcmp_up_lo("pwd", args[0]) == 0)
 		return (1);
 	if (ft_strcmp_up_lo("echo", args[0]) == 0)
 		return (1);
 	if (ft_strcmp_up_lo("env", args[0]) == 0)
 		return (1);
 	if (ft_strncmp("export", args[0], ft_strlen(args[0])) == 0)
 		return (1);
 	if (ft_strncmp("unset", args[0], ft_strlen(args[0])) == 0)
 		return (1);
	if (ft_strncmp("cd", args[0], ft_strlen(args[0])) == 0)
		return (1);
	return (0);
 }

int	ft_is_emptystr(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
			return (0);
		i++;
	}
	return (1);
}
