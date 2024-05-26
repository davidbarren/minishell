/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/26 21:46:46 by dbarrene         ###   ########.fr       */
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
	printf("address of input:%p\n", &input);
	ft_bzero(&input, sizeof(t_input));
	rl_bind_key('\t', rl_complete);
	using_history();
	parse_input(envp, &envs);
	input.envlist = &envs;
	baboonloop(&input);
	free_list(input.envlist);
//	free_input(&input);
	return (69);
}

void	baboonloop(t_input *input)
{
	char	*line;

	input->exit_status = 0;
	while (1)
	{
		line = NULL;
		line = readline("🐒baboonshell> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			input->exit_status = syntax_validation(line);
			printf("value of exit status:%d\n", input->exit_status);
			if (!input->exit_status)
			{
				prep_input(line, input);
				free_structs(input->arg_struct, input->pipe_count);
			}
			else if (input->exit_status)
				printf("value of status:%d\n", input->exit_status);
			free(line);
//			baboon_free(input->input);
		}
	}
}

void	free_input(t_input *input)
{
	if (input->pids)
		free(input->pids);
//	if (input->input)
//		free_2d(input->input);
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
		free(args->arglist);
	if (args->long_command)
		free(args->long_command);
	if (args->envcpy)
		free_2d(args->envcpy);
	if (args->split_path)
		free_2d(args->split_path);
	if (args->execpath)
		free(args->execpath);
	if (args->split_cmds)
		free_2d(args->split_cmds);
}
