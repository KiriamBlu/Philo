/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:17:37 by jsanfeli          #+#    #+#             */
/*   Updated: 2021/12/06 17:06:12 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_backstrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	while (s[i] && s[i] != c)
		i--;
	if (s[i] == c)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *) s1;
	i = strlen(str) - 1;
	j = 0;
	while (ft_strchr(set, (int)str[j]))
		j++;
	while (ft_backstrchr(set, (int)str[i]))
		i--;
	str = ft_substr(str, j, i - j + 1);
	if (!str)
		return (NULL);
	return (str);
}
