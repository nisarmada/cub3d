/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 13:07:04 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/23 14:52:22 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

// t_list	*ft_lstnew(void *content, char *left, char *right)
// {
// 	t_list	*new_node;

// 	new_node = (t_list *)malloc(sizeof(t_list));
// 	if (new_node == NULL)
// 		return (NULL);
// 	new_node->content = content;
// 	new_node->left = left;
// 	new_node->right = right;
// 	new_node->next = NULL;
// 	return (new_node);
// }

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = NULL;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int main()
// {
// 	t_list *new_node = ft_lstnew("yooo dude");

// 	printf("content: %s\n", (char *)new_node->content);
// 	return 0;
// }
