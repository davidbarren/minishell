/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:03:25 by plang             #+#    #+#             */
/*   Updated: 2024/05/08 15:21:35 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp_up_lo(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i] || s1[i] == s2[i] - 32 || s1[i] + 32 == s2[i])
		&& s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	cmd_is_builtin(t_env **envs, char **args)
{
	if(ft_strcmp_up_lo("pwd", args[0]) == 0)
		return (ft_pwd());
	if(ft_strcmp_up_lo("echo", args[0]) == 0)
		return (ft_echo(args));
	if(ft_strcmp_up_lo("env", args[0]) == 0)
		return (ft_env(envs));
	// if(ft_strncmp("pwd", args[0], ft_strlen(args[0])) == 0)
	// 	return (ft_pwd());
	// if(ft_strncmp("echo", args[0], ft_strlen(args[0])) == 0)
	// 	return (ft_echo(args));
	// if(ft_strncmp("env", args[0], ft_strlen(args[0])) == 0)
	// 	return (ft_env(envs));
	if(ft_strncmp("export", args[0], ft_strlen(args[0])) == 0)
		return (ft_export(envs, args));
	if(ft_strncmp("unset", args[0], ft_strlen(args[0])) == 0)
		return (ft_unset(envs, args));
	// if(ft_strncmp("cd", args[0], ft_strlen(args[0])) == 0)
	// 	return (ft_cd(envs, args));
	// if(ft_strncmp("exit", args[0], ft_strlen(args[0])) == 0)
	// 	return (ft_exit());
	return (1);
}
