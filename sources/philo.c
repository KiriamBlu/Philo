/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:50:35 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/10 17:29:31 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
# include"../header/philo_header.h"

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		putchar(str[i]);
		i++;
	}
}

void *managment(void *prueba)
{
	philo *ph;

	ph = (philo *)prueba;
	pthread_mutex_lock(&ph->lst.mutex);
	ph->lst.i++;
	printf("%i = %i\n", ph->index, ph->lst.i);
	pthread_mutex_unlock(&ph->lst.mutex);
	return (0);
}

int main(int argc, char const *argv[])
{
	gen philo_gen;
	philo  *ph;
	int i;

	i = 0;
	if(argc < 2)
	{
		printf("ERROR\n");
		return(0);
	}
	philo_gen.i = 0;
	philo_gen.philo_num = ft_atoi_special(argv[1]);
	philo_gen.thread = malloc(sizeof(pthread_t) * philo_gen.philo_num);
	ph = malloc(sizeof(philo) * philo_gen.philo_num);
	pthread_mutex_init(&philo_gen.mutex, NULL);
	while(i < philo_gen.philo_num)
	{
		ph[i].lst = philo_gen;
		ph[i].index = i;
		pthread_create(&philo_gen.thread[i], NULL, managment, &ph[i]);
		i++;
	}
	usleep(100000);
	return 0;
}