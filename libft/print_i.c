/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:44:39 by rardila-          #+#    #+#             */
/*   Updated: 2025/07/21 10:07:58 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	specialcase(void)
{
	write(1, "-2147483648", 11);
	return (11);
}

static int	ft_putnbr(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (specialcase());
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		len += ft_putnbr(nb / 10);
		len += ft_putchar(nb % 10 + '0');
	}
	else
	{
		len += ft_putchar(nb + '0');
	}
	return (len);
}

int	print_i(int param)
{
	return (ft_putnbr(param));
}
