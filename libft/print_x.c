/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:39:07 by rardila-          #+#    #+#             */
/*   Updated: 2025/07/21 10:08:43 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	hex_printer_cap(unsigned long hex)
{
	if (hex >= 16)
	{
		hex_printer_cap(hex / 16);
		hex_printer_cap(hex % 16);
	}
	else
	{
		if (hex < 10)
		{
			ft_putchar(hex + '0');
		}
		if (hex < 16 && hex > 9)
		{
			ft_putchar(hex + 'A' - 10);
		}
	}
	return ;
}

static void	hex_printer(unsigned long hex)
{
	if (hex >= 16)
	{
		hex_printer (hex / 16);
		hex_printer (hex % 16);
	}
	else
	{
		if (hex < 10)
		{
			ft_putchar(hex + '0');
		}
		if (hex < 16 && hex > 9)
		{
			ft_putchar(hex + 'a' - 10);
		}
	}
	return ;
}

static int	hex_len(unsigned long hex)
{
	int	count;

	if (hex == 0)
		return (1);
	count = 0;
	while (hex > 15)
	{
		hex = hex / 16;
		count++;
	}
	if (hex > 0)
		count++;
	return (count);
}

int	print_x(unsigned long hex, int cap)
{
	if (cap == 1)
		hex_printer_cap(hex);
	else
		hex_printer(hex);
	return (hex_len(hex));
}
