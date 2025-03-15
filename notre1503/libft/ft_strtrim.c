/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:28:34 by mobonill          #+#    #+#             */
/*   Updated: 2024/05/01 20:02:36 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	char	*s2;
	size_t	start;

	start = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
		end--;
	s2 = ft_substr(s1, start, (end - start + 1));
	return (s2);
}

// int	main(void)
// {
// 	char const *s1 = "wq 52.Hello There.5q 2wq2";
// 	char const *set = "25 .wq";
// 	char	*s2;
// 	s2 = ft_strtrim(s1, set);
// 	printf("%s\n", s2);
// }