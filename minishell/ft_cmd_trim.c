
#include "minishell.h"
//no solo contamos el numero de palabras sino que tambien este bien entre comillado.
static int	ft_count_words(const char *s, char *c, int i[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	//iteramos el prompt
	while (s[i[0]] != '\0')
	{
		//buscamos " " en el prompt
		if (!ft_strchr(c, s[i[0]]))
		{
			i[1]++;
			//en caso de que no se encuentre el " " o el contador aumente 
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				//comprobacion de que el inicio del prompt tenga comilla simple o doble
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				//se comprueba que el numero de veces que aparece debe ser par en caso de que no q[1] se reseteara a 0
				//para continuar con la cuenta, en todo caso si q[0] no es 0 al final es porque es impar el numero de comillas por tanto es un error
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3])
{
	int		s_len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(s);
	while (s[i[0]])
	{
		//buscamos la " " y guardamos lo recorrido como checkpoint en i[1]
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		{
			//el mismo caso comprobando los entre comillados
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		//comprobamos que no estemos en el final, en caso de estarlo acabamos la matrix de de strings
		//en caso contrario añadimos lla parte del prompt leida por eso guardamos recoridos en los iteradores i[1]
		if (i[1] >= s_len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

char	**ft_cmdtrim(char const *s, char *set)
{
	char	**aux;
	int		nwords;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words(s, set, counts);
	if (nwords == -1)
		return (NULL);
	//ya teneomso el numero de separaciones para los comandos
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	//obtenemos la matriz de cmd
	aux = ft_fill_array(aux, s, set, i);
	//finalizamos la ultima parte
	aux[nwords] = NULL;
	return (aux);
}