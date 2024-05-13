/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:56:39 by dbarrene          #+#    #+#             */
/*   Updated: 2024/05/13 14:14:33 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int		ft_pwd(void);
int		ft_echo(char **words);
int		ft_env(t_env **env);
int		ft_unset(t_env **env, char **cm_ar);
int		ft_strcmp_up_lo(char *s1, char *s2);
int		ft_export(t_env **envs, char **cmd_args);
t_env	*store_export_title_n_info(t_env *new_node, char *str);
int		check_duplicate_env(char *env_list_str, char *export_str, int what_env);
int		export_no_args(t_env **envs);
int		export_validation(char *args);
void	clean_from_quotes(char **str);
void	ft_export_clean(char **cmd_args);
void	change_lists_content(t_env **envs, char *new_env_str);
int		find_equal_sign(char *data);

#endif
