/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:26:44 by plang             #+#    #+#             */
/*   Updated: 2024/06/25 17:24:34 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
	{
		g_signal_exitstatus = 130;
		printf("\n");
	}
}

void	exec_sigquit(int signal)
{
	char	eof;

	eof = 4;
	if (signal != SIGQUIT)
		return ;
	if (signal == SIGQUIT)
	{
		g_signal_exitstatus = 131;
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("Quit: 3\n");
		ioctl(STDIN_FILENO, TIOCSTI, &eof);
	}
}

void	exec_signals(void)
{
	signal(SIGINT, exec_sigint);
	signal(SIGQUIT, exec_sigquit);
}
