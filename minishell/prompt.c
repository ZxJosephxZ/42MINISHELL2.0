/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:01:13 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/07/25 12:13:41 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;
//funcion que se encarga de obtener la ruta en la que nos encontramos, exceptuando el home por \~
static char *get_home(t_prompt prompt)
{
	char *temp;
	char *pwd;
	char *home;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = mini_getenv("HOME", prompt.envp, 4);
	//verificamos que no este vacio y comparamos las rutas eso obviara el home y sera reemplazado por \~
	if (home && home[0] && ft_strnstr(pwd , home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(temp);
	}
	free(home);
	//los espacios no son necesarios pero se ve mas ordenado en vez de tenerlo todo junto 
	//el color es solo un detalle si quieres lo quitamos para que luego no nos digan nada, respetando como funciona bash
	home = ft_strjoin(BLUE, pwd);
	free(pwd);
	pwd = ft_strjoin(home, " ");
	free(home);
	home = ft_strjoin(" ", pwd);
	free(pwd);
	pwd = ft_strjoin(home, DEFAULT);
	free(home);
	return (pwd);
}

//ESto no es necesario pero cualquier persona que ejecute esta minishell en su computadora tendra su propio nombre de host y su ruta correspondiente

static char *get_user(t_prompt prompt)
{
	char	**user;
	char	*temp;
	char	*temp2;

	user = NULL;
	temp2 = NULL;
	//ejecutamos whoami para saber el nombre del host y concatenar con los demas directorios y lo guardamos en user
	exec_customer(&user, "/usr/bin/whoami", "whoami", prompt.envp);
	//el nombre por defecto guest
	if (!user)
		user = ft_extend_matrix(user, "guest");
	//opcional
	if (!ft_strncmp(user[0], "root", 4))
		temp2 = ft_strjoin(NULL, RED);
	else if ((int)(user[0][0]) % 5 == 0)
		temp2 = ft_strjoin(NULL, CYAN);
	else if ((int)(user[0][0]) % 5 == 1)
		temp2 = ft_strjoin(NULL, GRAY);
	else if ((int)(user[0][0]) % 5 == 2)
		temp2 = ft_strjoin(NULL, GREEN);
	else if ((int)(user[0][0]) % 5 == 3)
		temp2 = ft_strjoin(NULL, MAGENTA);
	else
		temp2 = ft_strjoin(NULL, YELLOW);
	//concatenamos el final
	temp = ft_strjoin(temp2, *user);
	free(temp2);
	ft_free_matrix(&user);
	return (temp);
}

char	*mini_getprompt(t_prompt prompt)
{
	char	*temp;
	char	*temp2;
	char	*aux;

	//buscamos la ruta correspondiente
	temp = get_user(prompt);
	//concatenamos el indicador del programa minishell
	temp2 = ft_strjoin(temp, "@minishell");
	free(temp);
	//mostrar la ruta en la que nos encontramos al iniciarlizar el programa
	aux = get_home(prompt);
	//ruta del prompt completa
	temp = ft_strjoin(temp2, aux);
	free(aux);
	free(temp2);
	//simplemente verificamos la salida del programa en caso de ser una salida correcta azul y en caso contrario rojo
	//meramente opcional
	if (!g_status || g_status)
		temp2 = ft_strjoin(temp, BLUE);
	else
		temp2 = ft_strjoin(temp, RED);
	free(temp);
	//al final del prompt
	temp = ft_strjoin(temp2, "$ ");
	free(temp2);
	temp2 = ft_strjoin(temp, DEFAULT);
	free(temp);
	return (temp2);
}