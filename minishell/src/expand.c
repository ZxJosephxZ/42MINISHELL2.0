/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:21:29 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/08/20 16:53:17 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
extern int	g_status;

static char	*get_substr_var(char *str, int i, t_prompt *prompt)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	//buscamos el delimitador pos $ y le sumamos una posicion en caso de encontrar otro $ o ?
	pos = ft_strchars_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
	//si no encontramos algun delimetador tomamos la ultima posicion, que seria todo el prompot a ejecutar
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	//la variable auxiliar almacenara los datos que se encuentran antes del delimitador
	aux = ft_substr(str, 0, i - 1);
	//dependiendo de la variable de entorno o delimitador usado lo buscaremos en nuestro envp para 
	//obtener la ruta completa por ejemplo $HOME, nosotros no debemos ejecutar esto directamente
	//sino buscar la ruta HOME en nuestras envp y cambiar el prompt por /home/pramos
	var = mini_getenv(&str[i], prompt->envp, \
		ft_strchars_i(&str[i], "\"\'$|>< "));
	//en caso de tener como prompt el caso de $$ debemos mostrar el pid del proceso padre
	if (!var && str[i] == '$')
		var = ft_itoa(prompt->pid);
	//de ser un ? pues mostramos el tipo de proceso actual en el que se encuentra -> 0,127,31,etc
	else if (!var && str[i] == '?')
		var = ft_itoa(g_status);
	//establecemos el nuevo prompt y liberamos
	path = ft_strjoin(aux, var);
	free(aux);
	aux = ft_strjoin(path, &str[i + pos]);
	free(var);
	free(path);
	free(str);
	return (aux);
}

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~' && (i == 0 || \
			str[i - 1] != '$'))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}

char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		//comprobacion del entrecomillado interno de cada comando
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		//casos de dolar ademas del caso de comilla simple o doble al principio
		if (!quotes[0] && str[i] == '$' && str[i + 1] && \
		//ft_strchar_i se encargara de ver si hay un caracter especial devolviendo 1 o 0 que es true o false
			((ft_strchars_i(&str[i + 1], "/~%^{}:; ") && !quotes[1]) || \
			(ft_strchars_i(&str[i + 1], "/~%^{}:;\"") && quotes[1])))
			return (expand_vars(get_substr_var(str, ++i, prompt), -1, \
				quotes, prompt));
	}
	return (str);
}


