/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:22:18 by lbardet-          #+#    #+#             */
/*   Updated: 2025/10/20 04:28:09 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strcopy(char *s1, char *s2)
{
	char	*s3;

	if (!s1)
		s3 = ft_strjoin("", s2);
	else
	{
		s3 = ft_strjoin(s1, s2);
		free (s1);
	}
	return (s3);
}

char	*ft_read(char *str, int fd)
{
	char	*str1;
	int		bytes_read;

	str1 = malloc(BUFFER_SIZE + 1);
	if (!str1)
		return (NULL);
	bytes_read = read(fd, str1, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		str1[bytes_read] = 0;
		str = ft_strcopy(str, str1);
		if (ft_strchr(str, '\n'))
			break ;
		bytes_read = read(fd, str1, BUFFER_SIZE);
	}
	free(str1);
	if (bytes_read <= 0 && (!str || !*str))
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*ft_trimmedline(char *str)
{
	char	*str1;
	int		a;

	a = 0;
	while (str[a] && str[a] != '\n')
		a++;
	str1 = malloc(a + 2);
	if (!str1)
	{
		free (str1);
		return (NULL);
	}
	a = 0;
	while (str[a] && str[a] != '\n')
	{
		str1[a] = str[a];
		a++;
	}
	if (str[a] == '\n')
		str1[a++] = '\n';
	str1[a] = 0;
	return (str1);
}

char	*ft_save(char *str)
{
	char	*str1;
	int		a;
	int		b;
	int		c;

	a = 0;
	b = 0;
	c = ft_strlen(str);
	while (str[a] && str[a] != '\n')
		a++;
	if (str[a] == '\n')
		a++;
	str1 = malloc(c - a + 1);
	if (!str1)
		return (NULL);
	while (str[a])
		str1[b++] = str[a++];
	str1[b] = '\0';
	return (str1);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*str1;
	char		*str2;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read(str, fd);
	if (!str)
		return (NULL);
	str1 = ft_trimmedline(str);
	if (!str1)
	{
		free (str);
		str = NULL;
		return (NULL);
	}
	str2 = ft_save(str);
	free(str);
	str = str2;
	return (str1);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc != 2)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
