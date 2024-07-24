/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_euclideanddistance.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:10:03 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/07/24 09:23:48 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_euclideandistance(t_vector src, t_vector dest)
{
	return (ft_sqrt(ft_recursive_power(dest.x - src.x, 2) + \
							ft_recursive_power(dest.y - src.y, 2)));
}