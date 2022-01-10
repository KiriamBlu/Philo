/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:01:39 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/10 17:29:37 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<string.h>

//first part
void	*ft_memset(void *dest, int val, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//Second part
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char *s, char c);
void	*ft_memcpy(void *dest, const void *src, size_t len);
int		ft_atoi_special(const char *str);

#endif