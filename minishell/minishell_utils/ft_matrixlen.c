/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:10:25 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/07/24 12:18:05 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//calcular el numero de string en cada posicion del arreglo {1,2,3,4,null}

int	ft_matrixlen(char **m)
{
	int	i;

	i = 0;
	while (m && m[i])
		i++;
	return (i);
}