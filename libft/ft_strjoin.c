/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:33:45 by rardila-          #+#    #+#             */
/*   Updated: 2025/07/25 12:09:52 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1l;
	size_t	s2l;
	char	*str;

	s1l = 0;
	s2l = 0;
	if (s1)
		s1l = ft_strlen(s1);
	if (s2)
		s2l = ft_strlen(s2);
	str = malloc(s1l + s2l + 1);
	if (!str)
		return (0);
	ft_strlcpy (str, s1, s1l + 1);
	ft_strlcat (str, s2, s1l + s2l + 1);
	return (str);
}
