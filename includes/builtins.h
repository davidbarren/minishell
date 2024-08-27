/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:22:21 by plang             #+#    #+#             */
/*   Updated: 2024/06/25 17:22:31 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

//Inside pwd.c
int		ft_pwd(void);
//Inside echo.c
int		ft_echo(char **words);
//Inside env.c
int		ft_env(t_env **env);
//Inside unset.c
int		ft_unset(t_env **env, char **cm_ar);
int		ft_strcmp_up_lo(char *s1, char *s2);
//Inside all export.c files
int		ft_export(t_env **envs, char **cmd_args);
t_env	*store_export_title_n_info(t_env *new_node, char *str);
int		check_duplicate_env(char *env_list_str, char *export_str, int what_env);
int		export_no_args(t_env **envs);
int		export_validation(char *args);
void	clean_from_quotes(char **str);
void	ft_export_clean(char **cmd_args);
void	change_lists_content(t_env **envs, char *new_env_str);
int		find_equal_sign(char *data);
void	create_titleonly_node(t_env **envs, char *str, int flag);

#endif
