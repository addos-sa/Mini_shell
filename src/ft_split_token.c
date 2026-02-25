/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:34:16 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 15:51:12 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	clen(const char *s, char c)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && is_quote(s[i]))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else if (!quote && s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static int	count_c(const char *s, char c)
{
	int		v[2];
	char	quote;

	v[0] = 0;
	v[1] = 0;
	quote = 0;
	while (s[v[0]])
	{
		while (s[v[0]] == c)
			v[0]++;
		if (!s[v[0]])
			break ;
		v[1]++;
		while (s[v[0]])
		{
			if (!quote && is_quote(s[v[0]]))
				quote = s[v[0]];
			else if (quote && s[v[0]] == quote)
				quote = 0;
			else if (!quote && s[v[0]] == c)
				break ;
			v[0]++;
		}
	}
	return (v[1]);
}

static char	**free_calloc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static char	*copy_token(const char *s, size_t len)
{
	return (ft_substr(s, 0, len));
}

char	**ft_split_token(char const *s, char c)
{
	size_t	i;
	size_t	c_pos;
	size_t	len;
	char	**str;

	i = 0;
	c_pos = 0;
	str = ft_calloc(count_c(s, c) + 1, sizeof(char *));
	if (!str)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		len = clen(s + i, c);
		str[c_pos] = copy_token(s + i, len);
		if (!str[c_pos])
			return (free_calloc(str));
		c_pos++;
		i += len;
	}
	return (str);
}
