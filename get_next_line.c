/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <nsion@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:02:59 by nsion             #+#    #+#             */
/*   Updated: 2023/03/01 01:29:03 by nsion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stock;
	char	*line;
	char	buf[size];
	int	i;

	stock = (char *) malloc(sizeof(char) * ?? + 1);
	if (!stock)
		return (NULL);
	while (?? == '\n')
	stock += read(fd, buf, size);
	line = (char *) malloc(sizeof(char) * ?? + 1);
	if (!line)
		return (NULL;
	i = ft_strlen(stock);
	while (?i != '\n')
		line[i++] = stock[i++];
	buf[line] = '\0';
	return (buf[line] || line??)
}
