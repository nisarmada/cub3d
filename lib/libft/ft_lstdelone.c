/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 15:04:43 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/24 17:59:08 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstdelone(t_list *lst, void ((*del))(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}
