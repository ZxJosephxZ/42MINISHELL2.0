/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:59:02 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/07/24 13:37:35 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//sencillo buscamos que exista y tomamos el contenido desde despues del "=" y si no existe retornamos null
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
		//esta es la parte despues del "="
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return NULL;
}

char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	int i[2];
	char *aux[2];

	if (n < 0)
		n = ft_strlen(var);
	//primer iterador en -1 para aplicar el auto aumento con ++i y te ahorras una linea
	i[0] = -1;
	//concatenamos en un array las variables de la env y su contenido (clave=valor) ejem: [aux0] ->PWD -> "[aux1] + contenido"
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	//liberamos el sobrante
	free(aux[0]);
	//recorremos las variables de entorno y comprobamos que en nuestro contenido no exista un "=" ademas de que no este vacio las env que puede pasar por el env -i
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		//segundo iterador igual al numero de letras de la clave
		i[1] = n;
		//se va iterando y cambiado el iterador dependiendo de en que variable de entorno nos encontremos, en caso de encontrar esta se hace una actualizacion
		//esto para casos en donde existan cambios en el shlv o la ruta del pwd
		if (i[1] < ft_strchr_i(envp[i[0]], '='))
			i[1] = ft_strchr_i(envp[i[0]], '=');
		//se comprueba si la variable de entorno en donde nos encontramos como pwd, el iterador i[1] = 3 y se comprobaran estas 3 posiciones y cambiara
		//dependiendo de en que iteracion estamos este valor cambiara como con oldpwd o home, etc.
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{	aux[0] = envp[i[0]];
			envp[i[0]] = aux[1];
			free(aux[0]);
			return (envp);	
		}
	}
	//en caso de no encontrarse en las envp se añade esta nueva en la ultima posicion
	envp = ft_extend_matrix(envp, aux[1]);
	free(aux[1]);
	return (envp);
}

static	int 	var_in_envp(char *argc, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_i(argc, '=');
	if (pos == -1)
		return (-1);
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argc, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}

int	mini_export(t_prompt *prompt)
{
	int	ij[2];
	int	pos;
	char	**argc;

	argc = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argc) >= 2)
	{
		ij[0] = 1;
		while (argc[ij[0]])
		{
			pos = car_in_envp(argc[ij[0]], prompt->envp, ij);
			if (pos == 1)
			{
				free(prompt->envp[ij[1]]);
				prompt->envp[ij[1]] = ft_strdup(argc[ij[0]]);
			}
			else if (!pos)
				prompt->envp = ft_extend_matrix(prompt->envp, argc[ij[0]]);
			ij[0]++;
		}
	}
	return (0);
}

int	mini_unset(t_prompt *prompt)
{
	char	**argc;
	char	*aux;
	int	ij[2];

	ij[0] = 0;
	argc = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argc) >= 2)
	{
		while (argc[++ij[0]])
		{
			if (argc[++ij[0]][ft_strlen(argc[ij[0]]) -1] != '=')
			{
				aux = ft_strjoin(argc[ij[0]], "=");
				free(argc[ij[0]]);
				argc[ij[0]] = aux;
			}
			if (var_in_envp(argc[ij[0]], prompt->envp, ij))
				ft_matrix_replace_in(&prompt->envp, NULL, ij[1]);
		}
	}
	return (0);
}