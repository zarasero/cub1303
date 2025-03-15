/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:37:11 by mobonill          #+#    #+#             */
/*   Updated: 2024/04/23 17:10:39 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *ptr_dest, const void *ptr_src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*src;

	dest = (char *)ptr_dest;
	src = (const char *)ptr_src;
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
/*
int	main()
{
	char src[] = "hello, world";
	char dest[20];

	ft_memcpy(dest, src, sizeof(src));
	printf("src : %s\n", src);
	printf("dest : %s\n", dest);
}*/
