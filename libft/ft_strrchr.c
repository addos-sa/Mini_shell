/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:13:59 by rardila-          #+#    #+#             */
/*   Updated: 2025/05/07 13:41:37 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	lenght;
	char	*scpy;

	scpy = (char *)s;
	lenght = ft_strlen(s);
	while ((int)lenght >= 0)
	{
		if ((char) scpy [lenght] == (char)c)
			return ((char *)scpy + lenght);
		lenght--;
	}
	return (0);
}
