/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:25:14 by rardila-          #+#    #+#             */
/*   Updated: 2025/05/07 13:42:15 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hownmany_n(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	putnumbers(int n, char *str, int sign)
{
	int	charamount;
	int	temp;

	charamount = hownmany_n(n) + sign;
	temp = charamount - 1;
	while (n > 9 && temp > 0)
	{
		str[temp] = n % 10 + 48;
		n = n / 10;
		temp--;
	}
	if (n < 10)
		str[temp] = n + 48;
	if (sign == 1)
	{
		temp--;
		str[temp] = '-';
	}
}

char	*lownumber(void)
{
	char	*str;

	str = ft_calloc(12, sizeof(char));
	if (!str)
		return (0);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	return (str);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*str;

	if (n == -2147483648)
		return (lownumber());
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = n * -1;
	}
	str = ft_calloc(hownmany_n(n) + sign + 1, sizeof(char));
	if (!str)
		return (0);
	putnumbers(n, str, sign);
	return (str);
}
/*
int	main (void)
{
	printf("%s", ft_itoa (215));
	return (0);
}*/