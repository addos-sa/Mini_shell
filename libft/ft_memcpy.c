/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:11:32 by rardila-          #+#    #+#             */
/*   Updated: 2025/04/25 09:46:04 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int				i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	d = dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	while (i < (int)n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
