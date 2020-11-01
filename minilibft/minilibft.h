/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 17:50:40 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 12:29:41 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBFT_H
# define MINILIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <sys/types.h>
# include <dirent.h>
# define BUFF_SIZE 4096

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *nptr, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memalloc(size_t n);
void			*ft_memdup(const void *mem, size_t size);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_memdel(void **mem);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
char			*ft_ltoa(long n);
char			*ft_ultoa(unsigned long n);
int				ft_isdigit(int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_strsplit(const char *string, const char separator);
ssize_t			ft_putchar(char c);
ssize_t			ft_putstr(char const *s);
char			*ft_getfile(char *name, int fd);
void			ft_double_ptr_release(void **ptr);
char			*ft_find_str(char **str_array, char *str, uint32_t *i);
int				hex_to_uint(char *str, uint32_t *value);
void			ft_assert(int condition, char *message_on_fail);
int				ft_read_directory(const char *directory,
					void *addr_double_ptr, uint32_t *number);
#endif
