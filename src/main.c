/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/13 13:35:59 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs;
	t_input	input;
	char	*line;

	int status;
	(void) argc;
	(void) argv;
	envs = NULL;
	rl_bind_key('\t', rl_complete);
	using_history();
//	printf("Address of input in main: %p\n", &input);
	parse_input(envp, &envs);
	input.envlist = &envs;
//	printf("Address of envlist:%p\n", input.envlist);
	while (1)
	{
		line = NULL;
		line = readline("🐒baboonshell> ");
		if (!line)
			break ;
		add_history(line);
		status = syntax_validation(line);
		if (!status)
		{
			prep_input(line, &input);
			free_structs(input.arg_struct, input.pipe_count);
		}
		else if (status)
			printf("value of status:%d\n",status);	
		free(line);
//		printf("About to free my structs!\n");
		
//		free_input(&input);
	}
	free_list(input.envlist);
	return (69);
}
void	free_input(t_input *input)
{
//	printf("address of pid_array:%p\n", input->pids);
	if (input->pids)
		free(input->pids);
//	if (input->input)
//		free_2d(input->input);

}
void	free_structs(t_args **structs, int pipecount)
{
	int	i;
	i = 0;
//	printf("Address of structs headpointer:%p\n", structs);
	while (i < pipecount)
	{
//		printf("Address of structs at index:%d\n%p\n", i, structs[i]);
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
//		printf("Address of long command:%p\n", args->long_command);
		free(args->long_command);
	}
	if (args->tokenized_args)
	{
//		printf("Address of tokenargs:%p\n", args->tokenized_args);
//		free(args->long_command);
	}
//	printf("Address of pipes:%p\n",args->pipes);
//	printf("Address of envlist:%p\n",args->envlist);
}

