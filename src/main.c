/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/15 13:33:35 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs;
	t_input	input;

	(void) argc;
	(void) argv;
	envs = NULL;
	rl_bind_key('\t', rl_complete);
	using_history();
	parse_input(envp, &envs);
	input.envlist = &envs;
	baboonloop(&input);
	free_list(input.envlist);
	return (69);
}

void	baboonloop(t_input *input)
{
	char	*line;
	int		status;

	while (1)
	{
		line = NULL;
		line = readline("🐒baboonshell> ");
		if (!line)
			break ;
		add_history(line);
		status = syntax_validation(line);
		printf("status:%d\n", status);
		if (!status)
		{
			prep_input(line, input);
			free_structs(input->arg_struct, input->pipe_count);
		}
		else if (status)
			printf("value of status:%d\n", status);
		free(line);
	}
}

void	free_input(t_input *input)
{
	if (input->pids)
		free(input->pids);
}

void	free_structs(t_args **structs, int pipecount)
{
	int	i;

	i = 0;
	while (i < pipecount)
	{
		free_struct_content(structs[i]);
		free(structs[i]);
		i++;
	}
	free(structs);
}

void	free_struct_content(t_args *args)
{
	if (args->arglist)
	{
		free(args->arglist);
	}
	if (args->long_command)
	{
		free(args->long_command);
	}
}
