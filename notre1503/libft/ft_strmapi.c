/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:37:20 by mobonill          #+#    #+#             */
/*   Updated: 2024/05/01 20:04:07 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	i = 0;
	if (!s)
		return (NULL);
	dest = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	return (dest);
}

// char super_putchar(unsigned int index, char c)
// {
// 	printf("Le char est en position %d: %c!\n", index, c);
// 	return (c);
// }

// char add_one(unsigned int index, char c)
// {
// 	return (c + 1);
// }

// int main(void)
// {
// 	char *str = ft_strdup("Je suis un test\n");
// 	str = ft_strmapi(str, &super_putchar);
// 	str = ft_strmapi(str, &add_one);
// 	str = ft_strmapi(str, &super_putchar);
// 	str = ft_strmapi(str, &add_one);
// 	str = ft_strmapi(str, &super_putchar);

// }