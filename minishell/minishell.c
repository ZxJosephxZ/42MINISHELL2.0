/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:28:56 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/07/10 14:22:59 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Logica de los pipes para la ejecucion consiguiente

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

//Establece las variables de entorno y ademas condiciona el caso de (env -i)

static t_prompt init_vars(t_prompt prompt, char *str, char **argc)
{
	char *num;
	
	str = getcwd();
	prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
	free(str);
	str = mini_getenv("SHLVL", prompt.envp, 5);
	//Comprobacion del nivel del shlvl o su inicializacion
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
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
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(env);
	g_status = 0;
	mini_getpid(&prompt);
	prompt = init_vars(prompt, str, argc);
	return prompt;	
}

int main(int arc, char **argc, char **env)
{
	char	*out;
	char	*str;
	t_prompt	prompt;
	
	prompt = init_prompt(argc, envp);
	while(arc && arg)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = mini_getprompt(prompt);
		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell");
		free(str);
		if (!check_args(out, &prompt))
			break;
	}
	exit(g_status);
}