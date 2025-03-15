/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:08:35 by mobonill          #+#    #+#             */
/*   Updated: 2024/07/10 11:16:38 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_printf(char c)
{
	if (c == '\0')
		write(1, "\0", 1);
	else
		write(1, &c, 1);
	return (1);
}

int	ft_putstr_printf(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr_printf(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		nb = nb * -1;
		count++;
		ft_putchar_printf('-');
	}
	if (nb >= 10)
	{
		count += ft_putnbr_printf(nb / 10);
	}
	ft_putchar_printf(nb % 10 + '0');
	count++;
	return (count);
}

int	ft_putnbr_base_printf(unsigned long long nb, char *base,
		unsigned long long len)
{
	int	count;

	count = 0;
	if (nb >= len)
	{
		count += ft_putnbr_base_printf(nb / len, base, len);
	}
	count++;
	ft_putchar_printf(base[nb % len]);
	return (count);
}

int	ft_putaddress_printf(unsigned long long ptr)
{
	int	count;

	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	count = 2;
	count += ft_putnbr_base_printf(ptr, "0123456789abcdef", 16);
	return (count);
}
