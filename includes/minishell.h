/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:14:42 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/08 16:22:48 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include "../libft/includes/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmd
{
	struct s_cmd *next;
	struct s_cmd *prev;
	char **split_cmd;
}	t_cmd;

typedef struct s_env
{
	struct s_env *next;
	struct s_env *prev;
	char *env_element;
	int	index;
}	t_env;

typedef struct s_input
{
	char *input;
}	t_input;
void	store_env(char **ep, t_env **env);
t_env	*get_last_node(t_env *env);
t_env	*add_env_to_back(t_env *env, char *data, int index);
void	parse_input(char **ep, t_env *env);
void	print_list(t_env *env);
#endif
