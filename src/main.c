/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/05 15:32:00 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs = NULL;
	char	*input;
	int	i;
	if (argc && argv)
		i = 69;
	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		input = readline("baboonshell> ");
		if (!input)
			break;
		add_history(input);
		//store_input(input);
		ft_printf("input: %s\n", input);
		// add some shit here!
		free(input);
	}
	parse_input(envp, envs);
	return (69);
}
