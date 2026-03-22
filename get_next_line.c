/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakumcu <bakumcu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:10:30 by bakumcu           #+#    #+#             */
/*   Updated: 2026/03/22 13:08:26 by bakumcu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_store_line(int fd, char *stash)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
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

/*
* What this does is that it takes the line and goes until it
* sees a \n. then makes a dupe of the text starting from
* the second line as we have already printed the first line
*/

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

/*
* newline pos 
* get the line
* read the line 
* free the line 
* combine all in gnl
*/

/*
* We basically have to grab a text inside a file and go until we see
* newline. After the newline we take the line as the first line and 
* remaining as leftover. we go until all lines end
*/