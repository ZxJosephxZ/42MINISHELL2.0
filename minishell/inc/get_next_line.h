/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:54:51 by jpajuelo          #+#    #+#             */
/*   Updated: 2024/08/21 13:55:28 by jpajuelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 42

# endif

char	*get_next_line(int fd);

size_t	gnl_strlen(const char *s);

int		gnl_strchr_i(const char *s, int c);

size_t	gnl_strlcpy(char *dst, const char *src, size_t size);

char	*gnl_substr(char const *s, unsigned int start, size_t len);

size_t	gnl_strlcat(char *dst, const char *src, size_t size);

char	*gnl_shrink_buffer(char *buf, char *line);

char	*gnl_expand_buffer(char *buf, int fd);

char	*gnl_newread(int fd);

#endif