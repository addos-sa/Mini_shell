/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:27:38 by rardila-          #+#    #+#             */
/*   Updated: 2025/07/21 10:08:03 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
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

	count = 0;
	count += 2;
	while (hex > 15)
	{
		hex = hex / 16;
		count++;
	}
	if (hex > 0)
		count++;
	return (count);
}

int	print_p(void *p)
{
	int	count;

	count = 0;
	if (!p)
	{
		count += write (1, "(nil)", 5);
		return (count);
	}
	else
	{
		write (1, "0x", 2);
		hex_printer((unsigned long)p);
		return (hex_len ((unsigned long)p));
	}
}
