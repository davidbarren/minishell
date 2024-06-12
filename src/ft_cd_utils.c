/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:03:08 by dbarrene          #+#    #+#             */
/*   Updated: 2024/06/11 17:03:19 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_gohome(t_env **envs)
{
	char	*temp;

	temp = ft_getenv(envs, "HOME");
	chdir(temp);
	if (!temp)
		ft_printf("🐒: cd: HOME not set\n");
	free(temp);
	temp = NULL;
}

int	cd_badargs(char *str)
{
	ft_putstr_fd("🐒: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}
