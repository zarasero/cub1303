/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:17:40 by mobonill          #+#    #+#             */
/*   Updated: 2024/07/10 11:16:08 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ovpt(va_list args, const char c)
{
	int	count;

	count = 0;
	if (c == '%')
		count += ft_putchar_printf('%');
	else if (c == 'c')
		count += ft_putchar_printf(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr_printf(va_arg(args, char *));
	else if (c == 'd')
		count += ft_putnbr_printf(va_arg(args, int));
	else if (c == 'i')
		count += ft_putnbr_printf(va_arg(args, int));
	else if (c == 'u')
		count += ft_putnbr_base_printf(va_arg(args, unsigned int), "0123456789",
				10);
	else if (c == 'x')
		count += ft_putnbr_base_printf(va_arg(args, unsigned int),
				"0123456789abcdef", 16);
	else if (c == 'X')
		count += ft_putnbr_base_printf(va_arg(args, unsigned int),
				"0123456789ABCDEF", 16);
	else if (c == 'p')
		count += ft_putaddress_printf(va_arg(args, unsigned long long));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			i;
	static int	count;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_ovpt(args, str[i]);
		}
		else
		{
			ft_putchar_printf(str[i]);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

//
// int	main(void)
// {
// 	int		i;
// 	char	*str;
// 	int		o;
//
// 	i = 140;
// 	str = "ntm";
// 	o = ft_printf("%s\n", str);
// 	printf("count str = %d \n", o);
// 	ft_printf("count str de ft printf = %d \n", o);
// 	// ft_printf("%X\n", x);
// 	// printf("%p\n", &x);
// 	// ft_printf("%p", &x);
// }
//
// void test(int x, ...)
// {
// 	va_list args;
//
// 	va_start(args, x);
// 	// printf("%s\n", va_arg(args, char *));
// 	printf("%d\n", va_arg(args, int));
//
//
// 	va_end(args);
// }
//
// int	main(void)
// {
// 	test(0, "help", 123, 'k');
// }