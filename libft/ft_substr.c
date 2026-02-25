/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:47:46 by rardila-          #+#    #+#             */
/*   Updated: 2025/05/01 12:04:53 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*m_str;
	size_t	i;
	size_t	c;

	i = 0;
	if ((size_t)start > ft_strlen(s))
		start = (unsigned int) ft_strlen(s);
	c = ft_strlen(&s[start]);
	if (c > len)
		c = len;
	m_str = malloc(c + 1);
	if (!m_str)
		return (0);
	while (len > i && s[i])
	{
		m_str[i] = s[i + (size_t)start];
		i++;
	}
	m_str[i] = 0;
	return (m_str);
}
