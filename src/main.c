/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/29 17:49:04 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs;
	t_input	input;
	char	*line;

	(void) argc;
	(void) argv;
	envs = NULL;
	rl_bind_key('\t', rl_complete);
	using_history();
	printf("Address of input in main: %p\n", &input);
	parse_input(envp, &envs);
	input.envlist = &envs;
	printf("Address of envlist:%p\n", input.envlist);
	while (1)
	{
		line = NULL;
		line = readline("baboonshell> ");
		if (!line)
			break ;
		add_history(line);
		prep_input(line, &input);
		free(line);
	}
	return (69);
}
