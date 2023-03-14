/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:42:39 by nsion             #+#    #+#             */
/*   Updated: 2023/03/14 20:35:47 by nsion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_end(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s && s[i])
	{
		if (s[i] == '\n' || s[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*copy_line(char *stat, char *buf)
{
	char	*line;
	int		i;

	if (!stat || !ft_strlen(stat))
		return (NULL);
	i = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	line = (char *) malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stat[i] != '\n' && stat[i])
	{
		line[i] = stat[i];
		i++;
	}
	if (stat[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	if (buf)
		free(buf);
	return (line);
}

char	*new_line(char *stat)
{
	int		i;
	char	*str;

	i = 0;
	if (!stat)
	{
		// free(stat);
		// stat = NULL;
		return (NULL);
	}
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	str = ft_strdup(stat + i);
	printf("\n*~ %s ~*\n", str);
	if (stat)
		free(stat);
	return (str);
}

char	*get_next_line(int fd)
{
	int				stock;
	static char		*stat = NULL;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stat)
			free(stat);
		return (stat = NULL, NULL);
	}
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	stock = 1;
	while (find_end(stat) == 0 && stock > 0)
	{
		stock = read(fd, buf, BUFFER_SIZE);
		buf[stock] = '\0';
		stat = ft_strjoin(stat, buf);
	}
	//printf(" sat :%s\n", stat);
	// if (buf)
	// free(buf);
//		printf("lalala\n");
	// buf = NULL;
//	printf("buf_free%s\n", buf);
	buf = copy_line(stat, buf);
//	printf("buf_copy%s\n", buf);
	stat = new_line(stat);
	return (buf);
}


#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	printf("debut : \n");
	fd = open("text", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("main : %s", str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	printf("fin");
	return (0);
}
