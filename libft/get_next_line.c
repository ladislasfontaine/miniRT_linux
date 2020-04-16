/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 20:17:15 by marvin            #+#    #+#             */
/*   Updated: 2020/04/01 20:18:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_buf_to_line(char *buf, int n, char **line)
{
	char	*temp;
	int		i;
	
	i = 0;
	while (buf[n + i] && buf[n + i] != '\n')
		i++;
	temp = ft_strdup(*line);
	ft_strclr(*line);
	free(*line);
	if (!(*line = (char *)malloc(sizeof(char) * (ft_strlen(temp) + i + 1))))
	{
		free(temp);
		return (0);
	}
	*line[0] = '\0';
	*line = ft_strncat(*line, temp, (size_t)ft_strlen(temp));
	*line = ft_strncat(*line, buf + n, (size_t)i);
	ft_strclr(temp);
	free(temp);

	return (i);
}

int		get_next_line(int fd, char **line)
{
	char static	buf[BUFFER_SIZE + 1];
	int static	n;
	int static	res;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	*line = (char *)malloc(sizeof(char));
	*line[0] = '\0';
	while (1)
	{
		if (n == 0)
			if ((res = read(fd, buf, BUFFER_SIZE)) >= 0)
				buf[res] = '\0';
		n += add_buf_to_line(buf, n, line);
		if (buf[n] == '\n' || res < BUFFER_SIZE)
			break ;
		if (n >= res)
			n = 0;
	}
	n += 1;
	if (!res || (res < BUFFER_SIZE && n > res))
		return (0);
	if (n >= res)
		n = 0;
	return (1);
}
