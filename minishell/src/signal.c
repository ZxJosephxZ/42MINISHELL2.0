
#include "../inc/minishell.h"

int	g_status;
//sigint = ctrl+c  sigquit = ctrl + / invertida
//necesario para el manejo de las señales tanto para el proceso padre como los hijos
//en caso de interrupciones el valor devuelto es de 130
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		//la entrada por terminal y TIOCSTI es una macro que indica que vamos a pasar por terminal un puntero 
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//reemplza la salida y incerta un sato de liinea
		rl_replace_line("", 0);
		//te mueve a una nueva linea luego de incertar algun comado
		rl_on_new_line();
	}
}