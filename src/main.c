/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/12 14:18:52 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs;
	t_args	args;
	char	*input;
	(void) argc;
	(void) argv;
	envs = NULL;
	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		input = readline("baboonshell> ");
		if (!input)
			break ;
		add_history(input);
		prep_input(input, &args);
		free(args.arglist);
		free(input);
	}
	envs->index = 69;
	parse_input(envp, &envs);
	return (69);
}
