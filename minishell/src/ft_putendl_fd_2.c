/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:31:39 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/09/03 14:09:32 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_putendl_fd_2(char *s, int fd)
{
	if (s != NULL && ft_strchr(s,'='))
	{
		ft_putstr_fd_2(s, fd);
		ft_putchar_fd_2('\n', fd);
		return ((int)ft_strlen(s) + 1);
	}
	return (0);
}