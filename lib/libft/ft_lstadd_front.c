/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 14:55:02 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/24 11:56:38 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL || lst == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// int main ()
// {
// 	t_list	*head;
// 	t_list	*node1;
// 	t_list	*node2;

// 	head = ft_lstnew("head");
// 	node1 = ft_lstnew("node1");
// 	node2 = ft_lstnew("node2");
// 	printf("content: %s\n", head->content);
// 	ft_lstadd_front(&head, node1);
// 	printf("content: %s\n", head->content);
// }