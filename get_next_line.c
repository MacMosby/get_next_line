/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:31:25 by mrodenbu          #+#    #+#             */
/*   Updated: 2023/08/23 11:31:27 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_detect_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

char	*ft_next_line(char *str, int n)
{
	int		len;
	int		i;
	char	*line;

	if (n < 0 || !str)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	line = ft_calloc(len + 1, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = str[i];
		i++;
	}
	return (line);
}

char	*ft_shift(char *str, int n)
{
	int		start;
	int		i;
	char	*new;

	if (n < 0)
		free(str);
	if (n < 0 || !str)
		return (NULL);
	start = 0;
	while (str[start] && str[start] != '\n')
		start++;
	if (str[start] == '\n')
		start++;
	if (!str[start])
		return (free(str), NULL);
	new = ft_calloc(ft_strlen(str) - start + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	while (start + i < ft_strlen(str))
	{
		new[i] = str[start + i];
		i++;
	}
	return (free(str), new);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buff;
	char		*line;
	int			n;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	n = 1;
	while (ft_detect_line(str) == 0)
	{
		buff = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!buff)
			return (NULL);
		n = read(fd, buff, BUFFER_SIZE);
		if (n < 1)
		{
			free(buff);
			break ;
		}
		str = ft_strjoin(str, buff);
		free(buff);
	}
	line = ft_next_line(str, n);
	str = ft_shift(str, n);
	return (line);
}

/* int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	i = 0;
	while (i < 15)
	{
		line = get_next_line(fd);
		printf("line %d: %s", i + 1, line);
		free(line);
		i++;
	}
	return (0);
} */