/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:21:06 by gmartin-          #+#    #+#             */
/*   Updated: 2020/06/08 13:28:55 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_del(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (ptr);
}

static int		ft_return(int len, char **line)
{
	if (len < 0)
		return (-1);
	*line = ft_strdup("");
	return (0);
}

static char		*ft_line(char *auxfd, char **line, int *len)
{
	int		pos;
	char	*temp;

	pos = 0;
	while (auxfd[pos] != '\n' && auxfd[pos] != '\0')
		pos++;
	if (auxfd[pos] == '\n')
	{
		*line = ft_substr(auxfd, 0, pos);
		temp = ft_strdup(auxfd + (pos + 1));
		free(auxfd);
		auxfd = temp;
		if (auxfd[0] == '\0')
			auxfd = ft_del(auxfd);
		*len = 1;
	}
	else
	{
		*line = ft_strdup(auxfd);
		free(auxfd);
		auxfd = NULL;
		*len = 0;
	}
	return (auxfd);
}

int				get_next_line(int fd, char **line)
{
	static char *auxfd[4096];
	char		*buff;
	int			len;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((len = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[len] = '\0';
		if (auxfd[fd] == NULL)
			auxfd[fd] = ft_strdup(buff);
		else
			auxfd[fd] = ft_strjoin(auxfd[fd], buff);
		if (ft_strchr(auxfd[fd], '\n'))
			break ;
	}
	free(buff);
	if ((len < 0) || (len == 0 && auxfd[fd] == NULL))
		return (ft_return(len, line));
	auxfd[fd] = ft_line(auxfd[fd], line, &len);
	return (len);
}