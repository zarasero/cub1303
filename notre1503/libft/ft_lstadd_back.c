/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:37:48 by mobonill          #+#    #+#             */
/*   Updated: 2024/06/02 22:08:06 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nlast;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	nlast = ft_lstlast(*lst);
	nlast->next = new;
}

// int	main(void)
// {

// 	int a = 42;

// 	t_list *new = ft_lstnew(&a);
// 	printf("pointeur new el : %p\n", new);
// 	printf("pointeur new el : %d\n", *((int*)new->content));
// 	free(new);
// }