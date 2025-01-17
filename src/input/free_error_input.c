/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_error_input.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: elleneklund <elleneklund@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 16:57:54 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/19 17:04:48 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_colors(char **colors, char *value)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		free(colors[i]);
		i++;
	}
	free(colors);
	free(value); // double check at codam
}

int	error_msg(char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (status);
}
