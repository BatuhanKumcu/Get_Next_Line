/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakumcu <bakumcu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:10:30 by bakumcu           #+#    #+#             */
/*   Updated: 2026/05/16 20:49:39 by bakumcu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_join_and_free(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	free(stash);
	return (temp);
}

static char	*ft_read_store_line(int fd, char *stash)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while ((!stash) || (!ft_strchr(stash, '\n') && bytes > 0))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(stash), NULL);
		buffer[bytes] = '\0';
		stash = ft_join_and_free(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (stash);
}

static char	*ft_write_line(char *stash)
{
	int	len;

	if (!stash || !stash[0])
		return (NULL);
	if (ft_strchr(stash, '\n'))
		len = ft_strchr(stash, '\n') - stash + 1;
	else
		len = ft_strlen(stash);
	return (ft_substr(stash, 0, len));
}

static char	*ft_make_leftover(char *stash)
{
	char	*newline;
	char	*new_stash;

	newline = ft_strchr(stash, '\n');
	if (!newline)
	{
		free(stash);
		return (NULL);
	}
	if (*(newline + 1) == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(newline + 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_store_line(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_write_line(stash);
	stash = ft_make_leftover(stash);
	return (line);
}
