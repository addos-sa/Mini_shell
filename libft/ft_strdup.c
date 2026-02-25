/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:11:17 by rardila-          #+#    #+#             */
/*   Updated: 2025/04/30 12:28:46 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t		len;
	char		*mem;
	size_t		i;

	i = 0;
	len = ft_strlen(s) + 1;
	mem = malloc (len * sizeof(char));
	if (!mem)
		return (0);
	while (s[i])
	{
		mem[i] = s[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
