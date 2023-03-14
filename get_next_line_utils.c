/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:43:47 by nsion             #+#    #+#             */
/*   Updated: 2023/03/14 18:35:14 by nsion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*l;

	printf("\n*~ %s ~*\n", s);
	if (!s || !ft_strlen(s))
		return (NULL);
	i = 0;
	l = (char *)malloc(ft_strlen((s) + 1) * sizeof(char));
	if (l == 0)
		return (0);
	while (s[i])
	{
		l[i] = s[i];
		i++;
	}
	l[i] = '\0';
	return (l);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		l;
	int		i;
	int		k;

	// if (!s1 && !s2)
		// return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	// else if (!s2)
		// return (ft_strdup(s1));
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
