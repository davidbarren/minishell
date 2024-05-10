/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:56:39 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/10 12:51:39 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int	ft_pwd(void);
int	ft_echo(char **words);
int	ft_env(t_env **env);
int	ft_export(t_env **envs, char **cmd_args);
int	ft_unset(t_env **env, char **cm_ar);
int	ft_strcmp_up_lo(char *s1, char *s2);
#endif
