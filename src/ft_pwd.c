/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:57:26 by plang             #+#    #+#             */
/*   Updated: 2024/05/08 17:07:34 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		printf("\n%s\n", pwd);
		return (0); //EXIT_SUCCESS
	}
	else
		return (1); //EXIT_FAILURE
}
