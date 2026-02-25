/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:22:15 by rardila-          #+#    #+#             */
/*   Updated: 2025/04/28 10:35:12 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		src_l;
	size_t		dst_l;

	i = 0;
	src_l = ft_strlen(src);
	dst_l = ft_strlen(dst);
	if (dst_l >= size)
	{
		return (src_l + size);
	}
	while (i < (size - dst_l - 1) && src[i] != '\0')
	{
		dst[dst_l + i] = src[i];
		i++;
	}
	dst[dst_l + i] = '\0';
	return (dst_l + src_l);
}
