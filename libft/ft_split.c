/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:16:50 by rardila-          #+#    #+#             */
/*   Updated: 2025/05/05 16:59:56 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	clen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	count_c(const char *s, char c)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			count++;
			flag = 1;
		}
		if (s[i] == c && flag == 1)
			flag = 0;
		i++;
	}
	return (count);
}

char	**free_calloc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**str;
	int		c_pos;

	c_pos = 0;
	i = 0;
	str = ft_calloc(count_c(s, c) + 1, sizeof(char *));
	if (!str)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			str[c_pos] = ft_calloc(clen(s + i, c) + 1, sizeof(char));
			if (!str[c_pos])
				return (free_calloc(str));
			ft_memcpy (str[c_pos], s + i, clen(s + i, c));
			c_pos++;
		}
		i = i + clen(s + i, c) + 1;
		if (i > ft_strlen(s))
			return (str);
	}
	return (str);
}
