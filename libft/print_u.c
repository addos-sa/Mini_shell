/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:15 by rardila-          #+#    #+#             */
/*   Updated: 2025/07/21 10:08:38 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static int	putunsigned(unsigned int nb, int len)
{
	if (nb >= 10)
	{
		len += putunsigned(nb / 10, len);
		len++;
		ft_putchar(nb % 10 + '0');
	}
	else
	{
		ft_putchar(nb + '0');
		len++;
	}
	return (len);
}

int	print_u(unsigned int nb)
{
	return (putunsigned(nb, 0));
}
