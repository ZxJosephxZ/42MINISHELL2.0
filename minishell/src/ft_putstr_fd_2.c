/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:34:52 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/08/21 14:35:10 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_putstr_fd_2(char *s, int fd)
{
	if (s != NULL)
		return ((int)write(fd, s, ft_strlen(s)));
	return (0);
}