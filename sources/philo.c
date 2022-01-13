/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:50:35 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/01/13 14:04:00 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../header/philo_header.h"

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

void pressftotalk(philo *ph, int i)
{
	pthread_mutex_lock(&ph->lst->wait);
	if (i == 0)
		printf("Philo:%d is thinking %lu\n", ph->index, timestamp(ph));
	else if (i == 1)
		printf("Philo:%d left pick %lu\n", ph->index, timestamp(ph));
	else if (i == 2)
		printf("Philo:%d right pick %lu\n", ph->index, timestamp(ph));
	else if (i == 3)
		printf("Philo:%d is eating %lu\n", ph->index, timestamp(ph));
	else if (i == 4)
		printf("Philo:%d is sleeping %lu\n", ph->index, timestamp(ph));
	else if (i == 5)
		printf("Philo:%d is DEAD %lu\n", ph->index, checktime(ph));
	pthread_mutex_unlock(&ph->lst->wait);
}

void think(philo *ph)
{
	if(ph->lst->running == 1)
		pressftotalk(ph, 0);
	pthread_mutex_lock(ph->right);
	if(ph->lst->running == 1)
		pressftotalk(ph, 2);
	pthread_mutex_lock(ph->left);
	if(ph->lst->running == 1)
		pressftotalk(ph, 1);
}
void sleeping(philo *ph)
{
	if(ph->lst->running == 1)
	{
		pthread_mutex_unlock(ph->left);
		pthread_mutex_unlock(ph->right);
		pressftotalk(ph, 4);
	}
}

void *managment(void *prueba)
{
	philo *ph;
	ph = (philo *)prueba;
	ph->lasttime = ph->lst->firsttime;
	if (ph->index % 2 == 0)
			usleep(100);
	while(ph->lst->running == 1)
	{
		think(ph);
		getupdatetime(ph);
		if(ph->lst->running == 1)
			pressftotalk(ph, 3);
		myusleep(ph->lst->timetoeat, ph);
		sleeping(ph);
		myusleep(ph->lst->timetosleep, ph);
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
		ph[i].lst = philo_gen;
		ph[i].lasttime = ph[i].lst->firsttime;
		ph[i].index = i;
		ph[i].deathstatus = 0;
		ph[i].thread = philo_gen->threads[i];
		i++;
	}
	pthread_mutex_init(&philo_gen->forks[philo_gen->philo_num - 1], NULL);
	ph[i].left = &philo_gen->forks[i];
	ph[i].right = &philo_gen->forks[0];
	ph[i].lst = philo_gen;
	ph[i].lasttime = ph[i].lst->firsttime;
	ph[i].deathstatus = 0;
	ph[i].index = i;
	ph[i].thread = philo_gen->threads[i];
}

void deathswitch(philo *ph, int philo_num)
{
	int i;
	int k;

	while (1)
	{
		i = -1;
		while(++i < philo_num)
		{
			if (ph[i].lst->deathtime < checktime(&ph[i]))
			{
				k = -1;
				ph[i].lst->running = 0;
				pressftotalk(&ph[i], 5);
				return ;
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	gen philo_gen;
	philo  *ph;
	int k;
	int i;

	if(argc != 5 && argc != 6)
	{
		printf("ERROR\n");
		return(0);
	}
	k = 0;
	philo_gen.philo_num = ft_atoi_special(argv[1]) ;
	philo_gen.deathtime = (ft_atoi_special_l(argv[2]));
	philo_gen.timetoeat = (ft_atoi_special_l(argv[3]));
	philo_gen.timetosleep = (ft_atoi_special_l(argv[4]));
	pthread_mutex_init(&philo_gen.wait, NULL);
	gettimeofday(&philo_gen.reftime, NULL);
	philo_gen.firsttime = ((unsigned long)philo_gen.reftime.tv_sec * 1000) + ((unsigned long)philo_gen.reftime.tv_usec / 1000);
	philo_gen.forks = malloc(sizeof(pthread_mutex_t) * philo_gen.philo_num);
	philo_gen.threads = malloc(sizeof(pthread_t) * philo_gen.philo_num);
	philo_gen.running = 1;
	ph = malloc(sizeof(philo) * philo_gen.philo_num);
	phinit(ph, &philo_gen);
	i = -1;
	while (++i < philo_gen.philo_num)
		pthread_create(&ph[i].thread, NULL, managment, &ph[i]);
	deathswitch(ph, philo_gen.philo_num);
	return 0;
}
