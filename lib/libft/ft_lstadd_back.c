/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 14:06:02 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/23 14:52:47 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	node = NULL;
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		node = *lst;
		while ((node)->next)
		{
			node = node->next;
		}
		(node)->next = new;
	}
}

// int main()
// {
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	node1 = ft_lstnew("node1");
// 	node2 = ft_lstnew("node2");
// 	node3 = ft_lstnew("node3");
// 	node1->next = node2;
// 	// ft_lstadd_back(&node1, node2);
// 	ft_lstadd_back(&node1, node3);
// 	// printf("%s\n", (char *)node1->content);
// 	while (node1)
// 	{
// 		printf("%s\n", (char *)node1->content);
// 		node1 = node1->next;
// 	}
// }