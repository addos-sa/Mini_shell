/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:11:19 by rardila-          #+#    #+#             */
/*   Updated: 2025/04/30 11:38:12 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	if (!*little)
		return ((char *)big);
	while (len > i && big[i])
	{
		if (big[i] == little[0])
		{
			while (big[i + c] == little[c] && (i + c) < len)
			{
				c++;
				if (little[c] == '\0')
					return ((char *)&big[i]);
			}
			c = 0;
		}
		i++;
	}
	return (0);
}
