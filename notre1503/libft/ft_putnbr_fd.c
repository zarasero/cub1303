/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:48:58 by mobonill          #+#    #+#             */
/*   Updated: 2024/04/28 21:58:15 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n < 10)
		return (ft_putchar_fd(n + '0', fd));
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

// int	main(void)
// {
// 	int	fd = open("test.txt", O_WRONLY | O_CREAT, 0644);

// 	if (fd == -1)
// 	{
// 		perror("Erreur ouverture fichier");
// 		exit(EXIT_FAILURE);
// 	}
// 	ft_putnbr_fd(54246, fd);

// 	if (close(fd) == -1)
// 	{
// 		perror("Erreur fermeture fichier");
// 		exit(EXIT_FAILURE);
// 	}
// 	printf("Caracteres ecrits dans fichiers OK\n");

// 	return (0);
// }