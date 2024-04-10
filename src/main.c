/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/09 19:10:21 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs = NULL;
	t_args args;
	char	*input;
	int	i;
	t_input	line;
//	ft_memset(&envs, 0, sizeof(t_env));
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
		line.input = ft_strdup(input);
		ft_printf("input: %s\n", line.input);
		tokenize_input(&args, line.input);
		free(args.arglist);
		free(input);
	}
//	ft_printf("Address in main: %p\n", envs);
//	int k = 0;
//	while (envp[k])
//		ft_printf("Env:%s\n", envp[k++]);
	parse_input(envp, &envs);
//	print_list(envs);
	return (69);
}
