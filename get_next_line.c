/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:42:39 by nsion             #+#    #+#             */
/*   Updated: 2023/03/09 16:38:52 by nsion            ###   ########.fr       */
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
	int		stock;

	if (!stat)
		return (NULL);
	i = 0;
	while (stat[i] && stat[i] != '\n')
                i++;	
	printf ("in%d\n", i);
	line = (char *) malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (stat[++i] != '\n' && stat[i])
		line[i] = stat[i];
	if (stat[i] == '\n')
		line[i++] ='\n';
	line[i] = '\0';
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
//	printf("next firts= %s\n", next);
	if (next)
	{
//		printf("enter next\n");
		stat = ft_strdup(next);
		free(next);
		next = NULL;
	}
//	else
//		printf("next else\n");
//	if (!*next)
//		printf("next coquille");
//	if (!next)
//		printf("next pas de coquille\n");
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
	free(buf);
	buf = NULL;
	line = copy_line(stat);
	printf("line = %s\n", line);
	stock = ft_strlen(line);
	next = (char *) malloc(sizeof(char) * (ft_strlen(stat) - stock) + 1);
	if (!next)
		return (NULL);
//	if (next)
//		printf("next malloc\n");
	stock = -1;
	while (stat[++stock])
		next[stock] = stat[ft_strlen(line) + stock];
//	printf("next taille = %d\n", ft_strlen(next));
	if (ft_strlen(next) == 0 && next)
	{
//		printf("if coquille\n");
		free(next);
		next = NULL;
	}
//	if (!next)
//		printf("next supp\n");
//	printf("next = %d\n", ft_strlen(next));
	return (line);
}

#include <stdio.h>
int	main()
{
	int	fd;
	char	*str;
	int	i = 0;

	printf("debut\n");
	fd = open("text", O_RDONLY);
	str = get_next_line(fd);
	while (str && i < 10)
	{
		printf("main = %s", str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	printf("fin");
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
