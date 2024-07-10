/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:59:02 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/07/09 14:56:33 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//sencillo solo buscamos la existencia de las variables y en caso que no, introducimos el contenido
//con respecto a ft_strchr_i la unica modificacion realizada es que esta devuelve la posicion entera en donde se encuentra

char	*mini_getenv(char *var, char **envp, int n)
{
	int i;
	int n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_strsubstr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return NULL;
}

char	*mini_setenv(char *var, char *value, char **envp, int n)
{
	int i[2];
	char *aux;

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_i(envp[i[0]], '='))
			i[1] = ft_strchr_i(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{	aux[0] = envp[i[0]];
			envp[i[0]] = aux[1];
			free(aux[0]);
			return (envp);	
		}
	}
	envp = ft_extend_matrix(envp, aux[1]);
	free(aux[1]);
	return (envp);
}