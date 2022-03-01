/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:42:34 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/03/02 00:06:27 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sleepingandthink(t_philo	*philo)
{
	myusleep(philo->lst->timetoeat, philo);
	sleeping(philo);
	myusleep(philo->lst->timetosleep, philo);
	if (philo->lst->running == 1)
		pressftotalk(philo, 0);
}

void	*ft_memset(void *dest, int val, size_t len)
{
	unsigned char	*ptr;

	ptr = dest;
	while (len-- > 0)
		*ptr++ = val;
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	space;

	space = count * size;
	p = malloc (space);
	if (!p)
		return (NULL);
	ft_bzero(p, space);
	return (p);
}
