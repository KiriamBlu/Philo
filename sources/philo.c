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

unsigned long ft_atoi_special_l(const char *str)
{
	int				i[2];
	unsigned long	nb;

	i[0] = 0;
	i[1] = 0;
	nb = 0;
	while (str[i[0]] == ' ' || str[i[0]] == '\n' || str[i[0]] == '\t' \
			|| str[i[0]] == '\f' || str[i[0]] == '\v' || str[i[0]] == '\r')
		i[0]++;
	while (str[i[0]] >= '0' && str[i[0]] <= '9')
		nb = (nb * 10) + (str[i[0]++] - '0');
	if ((nb > 2147483647 && i[1] == 0) || (nb > 2147483648 && i[1] == 1))
	{
		write(1, "Error\n", 6);
		exit (0);
	}
	return (nb);
}

void getupdatetime(philo  *ph)
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

void *managment(void *prueba)
{
	philo *ph;
	ph = (philo *)prueba;
	if (ph->index % 2 == 0)
			usleep(100);
	gettimeofday(&ph->lst.reftime, NULL);
	ph->lasttime = ((unsigned long)ph->lst.reftime.tv_sec * 1000) + ((unsigned long)ph->lst.reftime.tv_usec / 1000);
	while(1)
	{
		printf("Philo:%d is thinking\n", ph->index);
		pthread_mutex_lock(ph->left);
		printf("Philo:%d left pick\n", ph->index);
		if (ph->lst.deathtime <= checktime(ph))
		{
			ph->lst.deathstatus = 1;
			printf("Philo:%d is DEAD after pick left: %lu\n", ph->index, checktime(ph));
		}
		if (ph->lst.deathstatus != 0)
			return(0);
		pthread_mutex_lock(ph->right);
		printf("Philo:%d right pick\n", ph->index);
		getupdatetime(ph);
		printf("Philo:%D TARDA:%lu\n", ph->index,ph->phdeath);
		if (ph->lst.deathtime <= checktime(ph))
		{
			ph->lst.deathstatus = 1;
			printf("Philo:%d is DEAD after pick right: %lu\n", ph->index, checktime(ph));
		}
		if (ph->lst.deathstatus != 0)
			return(0);
		printf("Philo:%d is eating\n", ph->index);
		usleep(ph->lst.timetoeat);
		if (ph->lst.deathtime <= checktime(ph))
		{
			ph->lst.deathstatus = 1;
			printf("Philo:%d is DEAD after eating: %lu\n", ph->index, checktime(ph));
		}
		if (ph->lst.deathstatus != 0)
			return(0);
		pthread_mutex_unlock(ph->left);
		printf("Philo:%d left drop\n", ph->index);
		pthread_mutex_unlock(ph->right);
		printf("Philo:%d right drop\n", ph->index);
		printf("Philo:%d is sleeping\n", ph->index);
		usleep(ph->lst.timetosleep);
		if (ph->lst.deathtime <= checktime(ph))
		{
			ph->lst.deathstatus = 1;
			printf("Philo:%d is DEAD after sleeping: %lu\n", ph->index, checktime(ph));
		}
		if (ph->lst.deathstatus != 0)
			return(0);
	}
	return (0);
}

void phinit(philo *ph, gen *philo_gen)
{
	int i;

	i = 0;
	while(i < philo_gen->philo_num - 1)
	{
		if (i == 0)
			pthread_mutex_init(&philo_gen->forks[0], NULL);
		pthread_mutex_init(&philo_gen->forks[i + 1], NULL);
		ph[i].left = &philo_gen->forks[i];
		ph[i].right = &philo_gen->forks[i + 1];
		ph[i].lst = *philo_gen;
		ph[i].index = i;
		ph[i].thread = malloc(sizeof(pthread_t) * 1);
		i++;
	}
	pthread_mutex_init(&philo_gen->forks[philo_gen->philo_num - 1], NULL);
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

	if(argc < 4  || argc > 5)
	{
		printf("ERROR\n");
		return(0);
	}
	philo_gen.philo_num = ft_atoi_special(argv[1]) ;
	philo_gen.deathtime = (ft_atoi_special_l(argv[2]));
	philo_gen.timetoeat = (ft_atoi_special(argv[3]) * 1000);
	philo_gen.timetosleep = (ft_atoi_special(argv[4]) * 1000);
	philo_gen.deathstatus = 0;
	philo_gen.forks = malloc(sizeof(pthread_mutex_t) * philo_gen.philo_num);
	ph = malloc(sizeof(philo) * philo_gen.philo_num);
	i = -1;
	phinit(ph, &philo_gen);
	while(++i < philo_gen.philo_num)
		pthread_create(&ph[i].thread, NULL, managment, &ph[i]);
	while(1)
		;
	printf("ALL DONE");
	usleep(100000);
	return 0;
}
