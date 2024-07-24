/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:10:00 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/07/24 12:12:17 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//matriz de arreglo es decir {"","","",NULL};

char	**ft_dup_matrix(char **m)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	//Obtenemos el numero de filas
	n_rows = ft_matrixlen(m);
	//Aumentamos en 1 para el null
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	//copiamos la matriz correspondiente 
	while (m[i])
	{
		out[i] = ft_strdup(m[i]);
		if (!out[i])
		{
			//en caso de error liberamos lo guardado en la matriz
			ft_free_matrix(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}