/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:40:47 by mobonill          #+#    #+#             */
/*   Updated: 2024/10/25 17:47:32 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_fprintf(int fd, char c)
{
	if (c == '\0')
		write(fd, "\0", 1);
	else
		write(fd, &c, 1);
	return (1);
}

int	ft_putstr_fprintf(int fd, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr_fprintf(int fd, int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		nb = nb * -1;
		count++;
		ft_putchar_fprintf(fd, '-');
	}
	if (nb >= 10)
	{
		count += ft_putnbr_fprintf(fd, nb / 10);
	}
	ft_putchar_fprintf(fd, nb % 10 + '0');
	count++;
	return (count);
}

int	ft_putnbr_base_fprintf(int fd, unsigned long long nb, char *base,
		unsigned long long len)
{
	int	count;

	count = 0;
	if (nb >= len)
	{
		count += ft_putnbr_base_fprintf(fd, nb / len, base, len);
	}
	count++;
	ft_putchar_fprintf(fd, base[nb % len]);
	return (count);
}

int	ft_putaddress_fprintf(int fd, unsigned long long ptr)
{
	int	count;

	if (ptr == 0)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	write(fd, "0x", 2);
	count = 2;
	count += ft_putnbr_base_fprintf(fd, ptr, "0123456789abcdef", 16);
	return (count);
}
