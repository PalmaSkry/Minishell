/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:00:59 by mg                #+#    #+#             */
/*   Updated: 2025/06/13 15:37:37 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_n_stash(int fd, char *buf, char *stash)
{
	int		read_line;
	char	*tmp;

	read_line = 1;
	while (read_line)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
		{
			free(buf);
			return (NULL);
		}
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!stash)
			stash = gnl_strdup("");
		tmp = stash;
		stash = gnl_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (gnl_strchr (buf, '\n'))
			break ;
	}
	return (stash);
}

char	*extract_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*next_in_stash(char *stash)
{
	int		i;
	int		j;
	char	*next_stash;
	size_t	len;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	len = ft_strlen(stash);
	next_stash = malloc(sizeof(char) * (len - i + 1));
	if (!next_stash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
	{
		next_stash[j] = stash[i];
		j++;
		i++;
	}
	next_stash[j] = '\0';
	free(stash);
	return (next_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	stash = read_n_stash(fd, buf, stash);
	free(buf);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = next_in_stash(stash);
	return (line);
}
