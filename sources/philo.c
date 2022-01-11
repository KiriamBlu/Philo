/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:50:35 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/11 15:50:28 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
# include"../header/philo_header.h"

void getupdatetime(philo  *ph)
{
	unsigned long i;

	gettimeofday(&ph->lst.reftime, NULL);
	i = ((unsigned long)ph->lst.reftime.tv_sec * 1000) + ((unsigned long)ph->lst.reftime.tv_usec / 1000);
	ph->lasttime = i - ph->lst.time;
}

void *managment(void *prueba)
{
	philo *ph;
	ph = (philo *)prueba;
	if (ph->index % 2 == 0)
			usleep(100);
	while(1)
	{
		getupdatetime(ph);
		printf("Timecheck:%lu\n", ph->lasttime);
		pthread_mutex_lock(ph->left);
		printf("Philo:%d left pick\n", ph->index);
		pthread_mutex_lock(ph->right);
		printf("Philo:%d right pick\n", ph->index);
		pthread_mutex_unlock(ph->left);
		pthread_mutex_unlock(ph->right);
		usleep(1000);
	}
	return (0);
}

void phinit(philo *ph, gen *philo_gen)
{
	int i;

	i = 0;
	while(i < philo_gen->philo_num - 1)
	{
		pthread_mutex_init(&philo_gen->forks[i], NULL);
		pthread_mutex_init(&philo_gen->forks[i + 1], NULL);
		ph[i].left = &philo_gen->forks[i];
		ph[i].right = &philo_gen->forks[i + 1];
		ph[i].lst = *philo_gen;
		ph[i].index = i;
		ph[i].thread = malloc(sizeof(pthread_t) * 1);
		ph[i].lasttime = 0;
		i++;
	}
	pthread_mutex_init(&philo_gen->forks[i], NULL);
	ph[i].left = &philo_gen->forks[i];
	ph[i].right = &philo_gen->forks[0];
	ph[i].lst = *philo_gen;
	ph[i].index = i;
	ph[i].thread = malloc(sizeof(pthread_t) * 1);
}

int main(int argc, char const *argv[])
{
	gen philo_gen;
	philo  *ph;
	int i;

	if(argc < 2 | gettimeofday(&philo_gen.reftime, NULL) == -1)
	{
		printf("ERROR\n");
		return(0);
	}
	philo_gen.time = ((unsigned long)philo_gen.reftime.tv_sec * 1000) + ((unsigned long)philo_gen.reftime.tv_usec / 1000);
	printf("%lu\n", philo_gen.time);
	philo_gen.philo_num = ft_atoi_special(argv[1]);
	philo_gen.forks = malloc(sizeof(pthread_mutex_t) * philo_gen.philo_num);
	ph = malloc(sizeof(philo) * philo_gen.philo_num);
	phinit(ph, &philo_gen);
	i = -1;
	while(++i < philo_gen.philo_num)
		pthread_create(&ph[i].thread, NULL, managment, &ph[i]);
	while(1)
		;
	usleep(100000);
	return 0;
}