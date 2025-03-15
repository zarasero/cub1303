/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:06:04 by mobonill          #+#    #+#             */
/*   Updated: 2024/05/01 20:11:19 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcount(char const *str, char c)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		len++;
		while (str[i] != c && str[i])
			i++;
	}
	return (len);
}

size_t	ft_charcount(char const *s, size_t i, char c)
{
	size_t	len;

	len = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] && s[i] != c)
	{
		if (s[i] == c)
			break ;
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	strcount;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	strcount = ft_strcount(s, c);
	res = (char **)ft_calloc(sizeof(char *), (strcount + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (j < strcount)
	{
		while (s[i] == c)
			i++;
		if (s[i])
			res[j++] = ft_substr(s, i, ft_charcount(s, i, c));
		if (j == (strcount))
			break ;
		while (s[i] != c)
			i++;
	}
	return (res);
}
/*
int main()
{
	char  *s = "      ceci       est un test      ";
	char    c = ' ';
	int  i = 0;
	char	**res;

	res = ft_split(s, c);
    while (res[i])
    {
        printf("%s\n", res[i]);
        free(res[i]);
        i++;
    }
    free(res);
}*/