/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:10:50 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/08/21 14:44:25 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_putnbr_base_fd(long n, char *base, int fd)
{
	int	count;
	int	base_len;

	count = 0;
	if (!base || !base[0] || ft_strlen(base) < 2)
		base = "0123456789";
	base_len = ft_strlen(base);
	if (n < 0)
	{
		count += write(1, "-", 1);
		n *= -1;
	}
	if (n >= base_len && n < 2147483648)
	{
		ft_putnbr_base_fd(n / base_len, base, fd);
		ft_putnbr_base_fd(n % base_len, base, fd);
	}
	else
		count += ft_putchar_fd_2(n + '0', fd);
	return (count);
}