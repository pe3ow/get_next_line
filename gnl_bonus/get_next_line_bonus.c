/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:22:18 by lbardet-          #+#    #+#             */
/*   Updated: 2025/10/21 07:47:18 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*ft_strcopy(char *s1, char *s2)
{
	char	*s3;

	if (!s1)
		return (ft_strjoin("", s2));
	s3 = ft_strjoin(s1, s2);
	free(s1);
	return (s3);
}

char	*ft_read(char *str, int fd)
{
	char	*str1;
	int		a;

	str1 = malloc(BUFFER_SIZE + 1);
	if (!str1)
		return (NULL);
	a = read(fd, str1, BUFFER_SIZE);
	while (a > 0)
	{
		str1[a] = '\0';
		str = ft_strcopy(str, str1);
		if (ft_strchr(str1, '\n'))
			break ;
		a = read(fd, str1, BUFFER_SIZE);
	}
	free(str1);
	if (a == -1)
	{
		free (str);
		return (NULL);
	}
	return (str);
}

char	*ft_trimmedline(char *str)
{
	char	*str1;
	int		a;

	if (!str || !*str)
		return (NULL);
	a = 0;
	while (str[a] && str[a] != '\n')
		a++;
	str1 = malloc(a + 2);
	if (!str1)
		return (NULL);
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

	a = 0;
	b = 0;
	while (str[a] && str[a] != '\n')
		a++;
	if (str[a] == '\n')
		a++;
	if (!str[a])
		return (NULL);
	str1 = malloc(ft_strlen(str) - a + 1);
	if (!str1)
		return (NULL);
	while (str[a])
		str1[b++] = str[a++];
	str1[b] = '\0';
	return (str1);
}

char	*get_next_line(int fd)
{
	static char	*str[MAX_FD];
	char		*str1;
	char		*str2;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (str[fd])
			free (str[fd]);
		return (NULL);
	}
	str[fd] = ft_read(str[fd], fd);
	if (!str[fd])
		return (NULL);
	str1 = ft_trimmedline(str[fd]);
	if (!str1)
	{
		free (str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	str2 = ft_save(str[fd]);
	free(str[fd]);
	str[fd] = str2;
	return (str1);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 1;
// 	if (argc < 2)
// 		return (1);
// 	while (argv[i])
// 	{
// 		fd = open(argv[i], O_RDONLY);
// 		if (fd == -1)
// 			return (1);
// 		line = get_next_line(fd);
// 		while (line)
// 		{
// 			printf("%s", line);
// 			free(line);
// 			line = get_next_line(fd);
// 		}
// 		close(fd);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
