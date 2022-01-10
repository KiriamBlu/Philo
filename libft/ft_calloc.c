/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:17:37 by jsanfeli          #+#    #+#             */
/*   Updated: 2021/12/06 17:05:12 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	space;

	space = count * size;
	p = malloc (sizeof(char) * space);
	if (!size)
		return (NULL);
	ft_bzero(p, space);
	return (p);
}
