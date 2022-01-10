/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:01:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2021/12/06 17:05:45 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getnumword(char const *s, char limit)
{
	size_t	i;

	i = 0;
	if (*s != limit && *s)
		i++;
	while (*(s + 1))
	{
		if (*s == limit && *(s + 1) != limit && *(s + 1) != '\0')
			i++;
		s++;
	}
	return (i);
}

static void	storagewords(char **str, char **auxi, char c, int getword)
{
	int		j;
	char	*aux;

	j = 0;
	if (getword != 0 && **str)
	{
		while (**str == c)
		{
			j++;
			*str = *str + 1;
		}
		aux = ft_strchr(*str, c);
		*auxi = ft_substr(*str, 0, aux - *str);
		j = 0;
		while (j < aux - *str)
			*str = *str + 1;
	}
}

char	**ft_split(char *s, char c)
{
	char	**aux;
	char	*str;
	int		n_words;
	int		i;

	i = 0;
	aux = NULL;
	if (s)
	{
		str = (char *)s;
		n_words = getnumword(str, c);
		aux = ft_calloc(n_words + 1, sizeof(char *));
		aux[n_words] = NULL;
		if (!aux)
			return (0);
		while (i < n_words)
		{
			storagewords(&str, &(aux[i]), c, n_words);
			i++;
		}
	}
	return (aux);
}
