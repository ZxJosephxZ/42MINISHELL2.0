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

char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	int i[2];
	char *aux[2];

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