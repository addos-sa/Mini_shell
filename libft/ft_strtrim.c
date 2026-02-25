/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:15:53 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/01 13:50:40 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isthesame(const char s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	i;
	size_t	c;
	size_t	j;
	char	*nstr;

	j = 0;
	i = 0;
	c = 0;
	if (!s1 || !set)
		return ((char *)s1);
	while (isthesame(s1[i], set) == 1 && s1[i] != '\0')
		i++;
	while (isthesame(s1[ft_strlen(s1) - c - 1], set) == 1 && i < ft_strlen(s1))
		c++;
	nstr = ft_calloc (((ft_strlen(s1) - i - c) + 1), sizeof(char));
	if (!nstr)
		return (0);
	while (j < (ft_strlen(s1 + i) - c))
	{
		nstr[j] = s1[j + i];
		j++;
	}
	free (s1);
	return (nstr);
}
