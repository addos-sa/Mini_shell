/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:37:15 by rardila-          #+#    #+#             */
/*   Updated: 2025/07/25 13:27:25 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*readit(char *save, int fd, int *read_bytes)
{
	char	*buffer;

	if (!save)
	{
		save = malloc(1 * sizeof(char));
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	*read_bytes = BUFFER_SIZE;
	while ((*read_bytes == BUFFER_SIZE) && (searchn(save) == 0))
	{
		*read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (*read_bytes < 0)
			return (ft_free(&buffer), ft_free(&save));
		buffer[*read_bytes] = '\0';
		save = ft_strjoingnl(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*cleanit(char *save, char *temp)
{
	int		i;
	int		k;

	i = 0;
	k = searchn(save);
	if (k > 0)
	{
		temp = malloc((k + 1) * sizeof(char));
		temp[k] = '\0';
		while (i < k)
		{
			temp[i] = save[i];
			i++;
		}
		return (temp);
	}
	temp = malloc(ft_strlen(save) * sizeof(char) + 1);
	temp[ft_strlen(save)] = '\0';
	while ((size_t)i < ft_strlen(save))
	{
		temp[i] = save[i];
		i++;
	}
	return (temp);
}

char	*saveit(char *save)
{
	char	*temp;
	int		i;

	i = 0;
	if (!save || BUFFER_SIZE <= 0)
		return (NULL);
	if (searchn(save) == 0 || (size_t)searchn(save) >= ft_strlen(save))
		return (ft_free(&save));
	temp = malloc(ft_strlen(save) - searchn(save) + 1);
	if (!temp)
		return (ft_free(&save));
	while ((ft_strlen(save) - (size_t)searchn(save)) > (size_t)i)
	{
		temp[i] = save[searchn(save) + i];
		i++;
	}
	temp[i] = '\0';
	free(save);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*line;
	int			read_bytes;
	char		*temp;

	temp = NULL;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	save = readit(save, fd, &read_bytes);
	if (save && save[0] == '\0')
	{
		free(save);
		save = NULL;
	}
	if (read_bytes > 0 || save != NULL)
		line = cleanit(save, temp);
	if (read_bytes == 0 && line != NULL)
	{
		free(save);
		save = NULL;
	}
	save = saveit(save);
	return (line);
}

// int	main(void)
// {
//     int		fd;
//     char	*line;

//     fd = open("prueba", O_RDONLY);
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);
//     return (0);
// }
