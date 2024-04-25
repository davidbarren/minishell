/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:47:32 by plang             #+#    #+#             */
/*   Updated: 2024/04/25 11:41:44 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h> // remove

int	we_have_redirect(char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] == '>')
	{
		ft_skip_char(&str, ' ');
		if (str[*i] == '\0')
			return (1);
	}
	if (str[*i] == '>' && str[*i + 1] == '<')
	{
		ft_skip_char(&str, ' ');
		if (str[*i] == '\0')
			return (1);
	}
	if (((str[*i + 1] == ' ' && str[*i + 2] == '>'))
		|| ((str[*i + 1] == ' ' && str[*i + 2] == '<')))
		return (1);
	if (((str[*i + 1] == '>' && str[*i + 2] == '>'))
		|| ((str[*i + 1] == '<' && str[*i + 2] == '<')))
		return (1);
	return (0);
}

int	valid_redirect(char *str)
{
	int i;
	int	check;

	i = 0;
	check  = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '>') || (str[i] == '<'))
			check = we_have_redirect(str, &i);
		if (check == 1)
			return (1);
		i++;
	}
	i--;
	while (str[i] == ' ')
		i--;
	if (str[i] == '>' || str[i] == '<')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	int	check;

	check = valid_redirect(argv[1]);
	printf("%d\n", check);
	return (0);
}

// int	valid_redirect(char *str)
// {
// 	int		check;
// 	char	temp;

// 	check = 0;
// 	while (*str != '\0')
// 	{
// 		if (*str == '<')
// 			temp = *str;
// 		else if (*str == '>')
// 			temp = *str;
// 		if (*str == ' ')
// 			ft_skip_char(&str, ' ');
// 		str++;
// 	}
// 	return (check);
// }
		// if (str[i] == '<' || str[i] == '>')
		// {
		// 	i++;
		// 	if (str[i] == ' ')
		// 	{
		// 		if ((str[i + 1]) == '<' || (str[i + 1]) == '>')
		// 		{
		// 			check = 1;
		// 			printf("yo");
		// 			break ;
		// 		}
		// 		ft_skip_char(&str, ' ');
		// 		if (str[i] == '\0' || str[i] == '>' || str[i] == '<')
		// 		{
		// 			check = 1;
		// 			printf("man");
		// 			break ;
		// 		}
		// 	}
		// }
		// i++;