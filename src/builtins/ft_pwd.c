/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:57:26 by plang             #+#    #+#             */
/*   Updated: 2024/04/23 16:24:34 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int	ft_pwd(void)
{
	char	pwd[1024];
	int		status;

	status = 0;
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		status = 1;
	return (status);
}

int	main(int argc, char **argv)
{
	int		i;
	char	*str;
	char	*pwd;

	if (argc == 2)
	{
		i = 0;
		str = argv[1];
		pwd = "pwd";
		if(ft_strncmp(pwd, str, sizeof(pwd)) == 0)
			ft_pwd();
	}
	return (0);
}
