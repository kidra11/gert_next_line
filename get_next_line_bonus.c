/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:32:49 by nsion             #+#    #+#             */
/*   Updated: 2023/03/16 16:34:40 by nsion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*copy_line(char *stat)
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
	return (line);
}

char	*new_line(char *stat)
{
	int		i;
	char	*str;

	i = 0;
	if (!stat)
		return (NULL);
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	str = ft_strdup(stat + i);
	if (stat)
		free(stat);
	return (str);
}

char	*reader(int fd, char *stat)
{
	char	*buf;
	int		stock;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	stock = 1;
	while (find_end(stat) == 0 && stock != 0)
	{
		stock = read(fd, buf, BUFFER_SIZE);
		if (stock == -1)
		{
			free(buf);
			buf = NULL;
		}
		buf[stock] = '\0';
		stat = ft_strjoin(stat, buf);
	}
	free(buf);
	return (stat);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stat[1000];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stat[fd])
			free(stat[fd]);
		return (stat[fd] = NULL, NULL);
	}
	stat[fd] = reader(fd, stat[fd]);
	line = copy_line(stat[fd]);
	stat[fd] = new_line(stat[fd]);
	return (line);
}

/*
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
}*/
