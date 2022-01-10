/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:17:37 by jsanfeli          #+#    #+#             */
/*   Updated: 2021/12/06 17:05:53 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;

	str = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (ft_memcpy(str, s1, ft_strlen(s1) + 1));
}
