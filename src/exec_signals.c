/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:26:44 by plang             #+#    #+#             */
/*   Updated: 2024/06/06 21:32:58 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
	{
		// es = 130;
		printf("\n");
	}
}

void	exec_sigquit(int signal)
{
	char eof;

	eof = 4;
	if (signal != SIGQUIT)
		return ;
	if (signal == SIGQUIT)
	{
		// es = 131;
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("Quit: 3\n");
		ioctl(STDIN_FILENO, TIOCSTI, &eof);
	}
}

void	exec_signals()
{
	signal(SIGINT, exec_sigint);
	signal(SIGQUIT, exec_sigquit);
}
