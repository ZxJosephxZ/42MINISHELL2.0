/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:28:56 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/07/25 12:22:02 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//POR CAMBIAR: Pero es para buscar el pid del principal del proceso

static void mini_getpid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mini_perror(FORKERR, NULL, 1);
		ft_free_matrix(&prompt->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&prompt->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

//Modificar las variables de entorno en caso de que tengamos problemas con el comando env -i

static t_prompt init_vars(t_prompt prompt, char *str, char **argc)
{
	char *num;
	
	//obtenemos la ruta del pwd
	str = getcwd();
	prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
	free(str);
	//siempre debemos pedir el shlvl porque puede variar por los subshells o scripts ademas de que un env -i lo resetea a 1
	str = mini_getenv("SHLVL", prompt.envp, 5);
	//Comprobamos el contenido entonces en caso de ser menor a 0 o null, lo inicializamos a 1
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	//actualizamos el shlvl igual que en los demas casos
	prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);
	free(num);
	//Este paso es necesario debido a que si no incorporo una ruta generica cuando nos quitan las env
	//el programa no va poder ejecutar los demas comandos.
	str = mini_getenv("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = mini_setenv("PATH", \
			"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
	//Lo que no me queda claro es que en bash, el path no esta definido en las env
	//cuando se hace un env -i bash pero aun asi siguen funcionando los comandos.
	str = mini_getenv("_", prompt.envp, 1);
	if (!str)
		prompt.envp = mini_setenv("_", argc[0], prompt.envp, 1);
	free(str);
	return (prompt);
}

//Metodo para inicializar la estructura
//Predefinimos las variables de entorno para en caso de un env -i (dejar variables basicas)


static t_prompt init_prompt(char **argc, char **env)
{
	t_prompt prompt;
	char	*str;
	
	str = NULL;
	//la dejamos null por ahora ya que aun no recibimos el prompt
	prompt.cmds = NULL;
	//hacemos una copia de las variables de entorno en caso de no inicializar el env -i de lo contrario se mantendra en null
	prompt.envp = ft_dup_matrix(env);
	//lo voy cambiar pero esto solo es para el control de salida del programa en este caso todo correcto 0
	g_status = 0;
	//Buscamos el pid principal del programa para no tener errores con los demas subprocesos, podria cambiarlo solo por un getpid pero luego hare los cambios.
	mini_getpid(&prompt);
	//aqui estoy implementando argc pero estan sencillo como hacerle un casting de (void) y dejar de usarlo
	prompt = init_vars(prompt, str, argc);
	return prompt;	
}

//La matriz que implementamos mas que una matriz bidimensional es un arreglo de string o argumentos
//Y la cola de tokens sera reemplazada por una lista enlazada que sera mas sencillo
//El inicio del nombre al ejecutar el programa se modifico para la obtencion de la ruta absoluta al directorio
//En bash ocurre esto asi que lo he cambiado ademas de la salida de errores, las he puesto en un enum para tenerlas inicializadas en vez de definir una macro por cada tipo de error


int main(int arc, char **argc, char **env)
{
	char	*out;
	char	*str;
	t_prompt	prompt;
	//aqui ya tenemos todo inicializado 
	prompt = init_prompt(argc, envp);
	
	while(arc && arg)
	{
		//manejamos las señales de manera correcta
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		//Esto es para marcar la ruta al iniciar el programa, simulando las acciones de bash.
		str = mini_getprompt(prompt);
		//habra dos opciones de mensaje en caso de no tener permisos para obtener la ruta o un pillo nos quite variable de entorno
		//se obtara por un guestminishell
		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell");
		free(str);
		//parseo
		if (!check_args(out, &prompt))
			break;
	}
	exit(g_status);
}