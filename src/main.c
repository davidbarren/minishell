/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/22 14:59:16 by dbarrene         ###   ########.fr       */
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
	while (1)
	{
		line = NULL;
		line = readline("baboonshell> ");
//		if (!quotes_num(line))
//			printf("syntax error");
//		printf("result of isredir: %d\n", ft_is_redirect(line));
		if (!line)
			break ;
		add_history(line);
		prep_input(line, &input);
		free(line);
	}
	// envs->index = 69;
	return (69);
}
