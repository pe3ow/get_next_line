/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:22:16 by lbardet-          #+#    #+#             */
/*   Updated: 2025/10/19 03:14:36 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	ft_strcat(char *s1, char const *s2)
{
	size_t	i;

	i = ft_strlen(s1);
	while (*s2)
		s1[i++] = *s2++;
	s1[i] = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	mallocsize;
	char	*s3;

	mallocsize = (ft_strlen(s1) + ft_strlen(s2));
	s3 = (char *)malloc(sizeof (char) * (mallocsize + 1));
	if (!s3)
	{
		free(s3);
		return (NULL);
	}
	s3[0] = 0;
	ft_strcat(s3, s1);
	ft_strcat(s3, s2);
	return (s3);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}