/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:17:37 by jsanfeli          #+#    #+#             */
/*   Updated: 2021/12/06 17:06:15 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		str = ft_calloc(1, sizeof(char));
		return (str);
	}
	if (len > ft_strlen(s) - start - 1)
		len = ft_strlen(s) - start;
	str = ft_calloc (len + 1, sizeof(char));
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	return (str);
}
