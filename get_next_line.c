/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:42:39 by nsion             #+#    #+#             */
/*   Updated: 2023/03/08 19:57:35 by nsion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		l;
	int		i;
	int		k;

	if (s1 == NULL)
	{
//		printf("s1 = %s\n", s2);
		return (ft_strdup(s2));
	}
	else if (!s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	l = 0;
	i = 0;
	k = 0;
	while (s1[i])
		str[l++] = s1[i++];
	while (s2[k])
		str[l++] = s2[k++];
	str[l] = '\0';
	free(s1);
	return (str);
}

int	find_end(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*copy_line(char *stat)
{
	char	*line;
	int		i;

	if (!stat)
		return (NULL);
	line = (char *) malloc(sizeof(char) * find_end(stat) + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stat[i] != '\n' && stat[i])
	{
		line[i] = stat[i];
		i++;
	}
	if (stat[i] == '\n')
	{
		line[i] = stat[i];
		i++;
	}
	line[i] = '\0';
	//printf ("line = %s\n", line);
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t		stock;
	static char	*next = NULL;
	char		*stat;
	char		*line;
	char		*buf;

	stat = NULL;
	if (next)
	{
//		printf("enter next\n");
		stat = ft_strdup(next);
	}
	free(next);
	next = NULL;
	if (!next)
//		printf("next pas de coquille\n");
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	stock = 1;
	while (find_end(stat) == 0 && stock > 0)
	{
//		printf("enter while\n");
		stock = read(fd, buf, BUFFER_SIZE);
		buf[stock] = '\0';
//		printf("buf = %s\n", buf);
		stat = ft_strjoin(stat, buf);
//		printf("stat = %s\n", stat);
	}
//	printf("out while\n");
	free(buf);
	buf = NULL;
	if (!buf)
//		printf("buf pas de coquille\n");
	line = copy_line(stat);
//	printf("line = %s\n", line);
	stock = ft_strlen(line);
	next = (char *) malloc(sizeof(char) * (ft_strlen(stat) - stock) + 1);
	if (!next)
		return (NULL);
	stock = -1;
	while (stat[++stock])
		next[stock] = stat[ft_strlen(line) + stock];
	printf("next = %s\n", next);
	return (line);
}

#include <stdio.h>
int	main()
{
	int	fd;
	char	*str;
	int	i = 0;

	fd = open("text", O_RDONLY);
	str = get_next_line(fd);
	while (str && i < 10)
	{
		printf("main = %s", str);
		free(str);
		str = get_next_line(fd);
		i++;
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
