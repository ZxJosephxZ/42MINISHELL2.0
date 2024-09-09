/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:27:47 by jpajuelo          #+#    #+#             */
/*   Updated: 2023/04/02 12:55:02 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/libft.h"

size_t	ft_strlcat(char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	lenstr1;
	size_t	lenstr2;

	lenstr1 = ft_strlen(str1);
	i = 0;
	if (n <= lenstr1)
	{
		lenstr2 = ft_strlen(str2) + n;
	}
	else
	{
		lenstr2 = lenstr1 + ft_strlen(str2);
		while (i + lenstr1 + 1 < n && str2[i])
		{
			str1[i + lenstr1] = str2[i];
			i++;
		}
		str1[i + lenstr1] = '\0';
	}
	return (lenstr2);
}
