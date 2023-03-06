/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:42:39 by nsion             #+#    #+#             */
/*   Updated: 2023/03/06 19:23:38 by nsion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		l;
	int		i;
	int		k;

	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return ((char *)s1);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	l = 0;
	i = 0;
	k = 0;
	while (s1[i])
		str[l++] = s1[i++];
	free(s1);
	while (s2[k])
		str[l++] = s2[k++];
	str[l] = '\0';
	return (str);
}

int	find_end(char *stat)
{
	int	i;

	i = 0;
	while (stat[i])
	{
		if (stat[i] != '\n')
			i++;
		else
			return (i);
	}
	return (0);
}

char	*copy_line(char *stat)
{
	char	*line;
	int		i;

	if (!stat)
		return (NULL);
	line = (char *) malloc(sizeof(char) * find_end(stat) + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (stat[++i] != '\n' && stat[i])
		line[i] = stat[i];
	line[i] = '\n';
	line[i++] = '\0';
	printf ("line = %s\n", line);
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t		stock;
	static char	*next = NULL;
	char		*stat;
	char		*line;
	char		*buf;

	buf = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (next)	
		stat = ft_strjoin(next, stat);
	while (find_end(stat) > 0 || stock > 0)
	{		
		stock = read(fd, buf, BUFFER_SIZE);
		buf[stock] = '\0';
		stat = ft_strjoin(stat, buf);
	}
	printf("buf = %s\n", buf);
	free(buf);
	line = copy_line(stat);
	stock = ft_strlen(line);
	next = (char *) malloc(sizeof(char) * (ft_strlen(stat) - stock) + 1);
	if (!next)
		return (NULL);
	stock = -1;
	while (stat[++stock])
		next[stock] = stat[ft_strlen(line) + stock];
	free(stat);
	return (line);
}

#include <stdio.h>
int	main()
{
	int	fd;
	char	*str;

	fd = open("text", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("main = %s", str);
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}
/*
test :
salut\n
je suis un poulet\n

malloc buf
buf read > salut
line > salut
2eme
buf read > \nje s
line > salut\nje s
next > je s
*/
