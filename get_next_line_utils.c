/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakumcu <bakumcu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 14:38:51 by bakumcu           #+#    #+#             */
/*   Updated: 2026/05/16 20:01:09 by bakumcu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == 0)
		return ((char *)s + i);
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*sum;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1)
		i = ft_strlen(s1);
	if (s2)
		j = ft_strlen(s2);
	sum = malloc(sizeof(char) * (i + j + 1));
	if (!sum)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		sum[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		sum[i++] = s2[j++];
	sum[i] = '\0';
	return (sum);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	while (s[i] != 0)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(const char *s, unsigned int start, size_t n)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (n > ft_strlen(s + start))
		n = ft_strlen(s + start);
	str = malloc((n + 1) * (sizeof(char)));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
