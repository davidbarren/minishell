/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:57:20 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/04 13:01:48 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int		silly_atoi(char *code)
{

}
*/
void	exit_bad_args(char **args, int status)
{
	if (status == 1)
	{
		ft_printerror("exit\n");
		ft_printerror("baboonshell: exit: %s: numeric argument required\n",
			args[1]);
		exit (255);
	}
	else if (status == 2)
	{
		ft_printerror("exit\n");
		ft_printerror("baboonshell: exit: too many arguments\n");
	}
}

void	exit_good(int code)
{
	write(1, "exit\n", 5);
	exit(code);
}

void	ft_exit(char **args)
{
	int	code;
	int	argc;

	argc = ft_arrlen(args);
	if (argc == 1)
		exit_good (0);
	if (args[1][0] == '0')
		exit_good(0);
	code = ft_atoi(args[1]);
	if (!code)
		exit_bad_args(args, 1);
	if (argc > 2)
	{
		exit_bad_args(args, 2);
		return ;
	}
	exit_good(code);
}
