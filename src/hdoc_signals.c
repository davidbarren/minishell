/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:26:53 by plang             #+#    #+#             */
/*   Updated: 2024/06/06 21:32:48 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	modify_termios_hdoc(struct termios *tios)
{
	tios->c_cc[VQUIT] = _POSIX_VDISABLE;
	tios->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, tios);
}

void	reset_termios_hdoc(struct termios *tios)
{
	tios->c_cc[VQUIT] = 034;
	tios->c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, tios);
}

void	heredoc_sigint(int signal)
{
	char eof;

	eof = 4;
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
	{
		//es = 1;
		printf("\n");
		ioctl(STDIN_FILENO, TIOCSTI, &eof);
	}
}

void	heredoc_signals()
{
	signal(SIGINT, heredoc_sigint);
}