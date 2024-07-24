/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixtolst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:10:29 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/07/24 09:45:10 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_list	*ft_matrixtolst(char **matrix)
{
	t_list	*lst;
	int		i;

	lst = NULL;
	i = -1;
	while (matrix[++i])
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(matrix[i])));
	return (lst);
}