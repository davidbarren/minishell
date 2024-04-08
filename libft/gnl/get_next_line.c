/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:22:31 by dbarrene          #+#    #+#             */
/*   Updated: 2023/12/16 11:55:09 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin_mod(char *s1, const char *s2)
{
	char	*joined;
	size_t	i;

	if (!s1)
		return (ft_strdup(s2));
	joined = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
	{
		if (s1)
			free (s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = 0;
	free(s1);
	return (joined);
}

char	*trimtheline(char *totline)
{
	char	*temp;
	int		i;

	i = ft_strlen_mod(totline, '\n');
	i++;
	temp = totline;
	totline = ft_substr_mod(totline, i, BUFFER_SIZE);
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	return (totline);
}

char	*copy_newline(char *newline, char *totline)
{
	int	i;
	int	j;

	if (totline[0] == 0)
		return (NULL);
	i = ft_strlen_mod(totline, '\n');
	j = 0;
	if (ft_strchr_mod(totline, '\n'))
		newline = malloc (i + 2);
	else if (!ft_strchr_mod(totline, '\n'))
		newline = malloc (i + 1);
	if (!newline)
		return (NULL);
	while (totline[j] != '\n' && totline[j])
	{
		newline[j] = totline[j];
		j++;
	}
	if (totline[j] == '\n')
	{
		newline[j] = '\n';
		j++;
	}
	newline[j] = 0;
	return (newline);
}

char	*read_line(int fd, char *totline)
{
	int		bytes_read;
	char	temp[BUFFER_SIZE + 1];
	char	*storage;

	bytes_read = 1;
	while (!ft_strchr_mod(totline, '\n') && (bytes_read != 0))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			if (totline)
			{
				free(totline);
				totline = NULL;
			}
			return (NULL);
		}
		temp[bytes_read] = 0;
		storage = ft_strjoin_mod(totline, temp);
		if (!storage)
			return (NULL);
		totline = storage;
	}
	return (totline);
}

char	*get_next_line(int fd)
{
	static char	*totline = NULL;
	char		*newline;

	newline = NULL;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	totline = read_line(fd, totline);
	if (!totline)
		return (NULL);
	newline = copy_newline(newline, totline);
	if (!newline)
	{
		free (totline);
		totline = NULL;
		return (NULL);
	}
	totline = trimtheline(totline);
	return (newline);
}
