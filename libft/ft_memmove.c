/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:53:45 by rardila-          #+#    #+#             */
/*   Updated: 2025/04/25 11:15:32 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp;
	unsigned char	*dest1;

	temp = (unsigned char *)src;
	dest1 = (unsigned char *)dest;
	if (!dest && !src)
		return (0);
	if (dest1 >= temp)
	{
		while (n--)
		{
			dest1[n] = temp[n];
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
