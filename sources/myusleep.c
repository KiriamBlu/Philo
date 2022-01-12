/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myusleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:56 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/12 13:46:24 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../header/philo_header.h"

unsigned long timestamp(philo *ph)
{
	unsigned long i;

	gettimeofday(&ph->lst.reftime, NULL);
	i = ((unsigned long)ph->lst.reftime.tv_sec * 1000) + ((unsigned long)ph->lst.reftime.tv_usec / 1000);
	return(i - ph->lst.firsttime);
}

void getupdatetime(philo *ph)
{
	unsigned long i;

	gettimeofday(&ph->lst.reftime, NULL);
	i = ((unsigned long)ph->lst.reftime.tv_sec * 1000) + ((unsigned long)ph->lst.reftime.tv_usec / 1000);
	ph->phdeath = i - ph->lasttime;
	ph->lasttime = i;
}

unsigned long checktime(philo *ph)
{
	unsigned long i;

	gettimeofday(&ph->lst.reftime, NULL);
	i = ((unsigned long)ph->lst.reftime.tv_sec * 1000) + ((unsigned long)ph->lst.reftime.tv_usec / 1000);
	return(i - ph->lasttime);
}

void	myusleep(unsigned long microsec, philo *ph)
{
	unsigned long i;
	unsigned long k;

	gettimeofday(&ph->lst.reftime, NULL);
	i = ((unsigned long)ph->lst.reftime.tv_sec * 1000) + ((unsigned long)ph->lst.reftime.tv_usec / 1000);
	k = i + microsec;
	while(i < k)
	{
		usleep(100);
		gettimeofday(&ph->lst.reftime, NULL);
		i = ((unsigned long)ph->lst.reftime.tv_sec * 1000) + ((unsigned long)ph->lst.reftime.tv_usec / 1000);
	}
}