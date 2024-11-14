/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/27 13:27:39 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/27 16:42:55 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*head;
	t_list	*newlist;

	if (!lst || !del || !f)
		return (0);
	newlist = NULL;
	newlist = ft_lstnew(f(lst->content));
	if (!newlist)
		return (0);
	head = newlist;
	lst = lst->next;
	while (lst)
	{
		newlist->next = ft_lstnew(f(lst->content));
		if (!newlist->next)
			ft_lstclear(&head, del);
		lst = lst->next;
		newlist = newlist->next;
	}
	newlist->next = NULL;
	return (head);
}
