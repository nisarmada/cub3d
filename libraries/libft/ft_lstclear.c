/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 15:46:59 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/24 17:30:38 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		node = *lst;
		*lst = (*lst)->next;
		del(node->content);
		free(node);
	}
}
