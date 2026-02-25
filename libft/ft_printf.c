/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:10:28 by rardila-          #+#    #+#             */
/*   Updated: 2025/07/21 10:07:34 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_alt(const char s, va_list arg)
{
	int	cap;

	cap = 0;
	if (s == 'X' && arg)
		cap = 1;
	if ((s == 'i' || s == 'd') && arg)
		return (print_i(va_arg(arg, int)));
	if (s == 's')
		return (print_s(va_arg(arg, char *)));
	if (s == 'c' && arg)
		return (print_c(va_arg(arg, int)));
	if (s == '%' && arg)
		return (print_percent());
	if (s == 'u' && arg)
		return (print_u(va_arg(arg, unsigned int)));
	if ((s == 'x' || s == 'X') && arg)
		return (print_x(va_arg(arg, unsigned int), cap));
	if (s == 'p' && arg)
		return (print_p(va_arg(arg, void *)));
	return (0);
}

static int	nolesszero(int esc)
{
	if (esc < 0)
		return (0);
	return (esc);
}

int	ft_printf(char const *s, ...)
{
	int		i;
	int		esc;
	va_list	arg;

	i = 0;
	esc = 0;
	va_start(arg, s);
	while (s[i])
	{
		if (s[i] == '\b')
			esc += -2;
		if (s[i] == '%')
		{
			i++;
			if (s[i])
			{
				esc += print_alt(s[i], arg);
			}
		}
		else
			esc += write (1, &s[i], 1);
		i++;
	}
	va_end(arg);
	return (nolesszero(esc));
}

// int	main(void)
// {
// 	int		a;
// 	char	string[] = "strin";

// 	a = ft_printf("\b");
// 	ft_printf(" PRUEBA ||| Caracteres imprimidos %i\n", a);
// 	a = ft_printf("%s\n", string);
// 	ft_printf(" STRING ||| Caracteres imprimidos %i\n", a);
// 	a = ft_printf("%i\n", -12345);
// 	ft_printf(" INT ||| Caracteres imprimidos %i\n", a);
// 	a = ft_printf("%i\n", -2147483648);
// 	ft_printf(" INT ||| Caracteres imprimidos %i\n", a);
// 	a = ft_printf("%d\n", 215);
// 	ft_printf(" DECIMAL ||| Caracteres imprimidos %i\n", a);
// 	a = ft_printf("%c\n", 'h');
// 	ft_printf(" CHARACTER ||| Caracteres imprimidos %i\n", a);
// 	a = ft_printf("%%\n");
// 	ft_printf(" PERCENT ||| Caracteres imprimidos %i\n", a);
// 	a = ft_printf("%u\n", 445);
// 	ft_printf(" UNSIGNED INT ||| Caracteres imprimidos %i\n", a);
// 	a = ft_printf("%x\n", 0);
// 	ft_printf(" HEX ||| Caracteres imprimidos %i\n", a);
// 	a = printf("%X\n", 0);
// 	printf(" HEX CAP ||| Caracteres imprimidos %i\n", a);
// 	a = ft_printf("%p\n", *string);
// 	ft_printf(" VOID POINTER ||| Caracteres imprimidos %i\n", a);
// 	return (0);
// }