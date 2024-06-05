/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:54 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/05 18:24:07 by dbarrene         ###   ########.fr       */
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
	ft_bzero(&input, sizeof(t_input));
	rl_bind_key('\t', rl_complete);
	using_history();
	parse_input(envp, &envs);
	input.envlist = &envs;
	baboonloop(&input);
	free_list(input.envlist);
	return (0);
}

void	baboonloop(t_input *input)
{
	char	*line;
	int		syntax_status;

	syntax_status = 0;
	while (1)
	{
		line = NULL;
		line = readline("🐒baboonshell> ");
		if (!line)
			break ;
		if (*line && !ft_emptyline(line))
		{
			add_history(line);
			syntax_status = syntax_validation(line);
			if (!syntax_status)
				input_valid_routine(input, line);
			else if (syntax_status)
				input->exit_status = syntax_status;
			free(line);
		}
	}
}

void	free_input(t_input *input)
{
	if (input->pids)
		free(input->pids);
	if (input->pipes)
		free(input->pipes);
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
	if (args->redirects)
		free_redirs(args->redirects);
}
