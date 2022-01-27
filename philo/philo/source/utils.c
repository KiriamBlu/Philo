/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:40:34 by jporta            #+#    #+#             */
/*   Updated: 2022/01/26 18:12:00 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_finthread(t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < gen->philo_num)
		pthread_mutex_destroy(&gen->mutex_forks[i]);
	pthread_mutex_destroy(&gen->wait);
	free(gen->threads);
}

int	ft_errors(int argc, char **argv)
{
	int		i;
	long	aux;

	i = 0;
	if (argc != 6 && argc != 5)
		return (1);
	while (++i < argc)
	{
		aux = ft_atoi_special(argv[i]);
		if (aux > 2147483648 || aux <= 0)
		{
			printf("AQUI\n");
			return (1);
		}
	}
	return (0);
}

t_gen	structinit(char **argv, int argc)
{
	t_gen	gen;

	gen = (t_gen){
		.philo_num = ft_atoi_special(argv[1]),
		.deathtime = (ft_atoi_special_l(argv[2])),
		.timetoeat = (ft_atoi_special_l(argv[3])),
		.timetosleep = (ft_atoi_special_l(argv[4])), .running = 0
	};
	if (argc == 6)
	{
		gen.count = 0;
		gen.eattime = (ft_atoi_special_l(argv[5]));
	}
	pthread_mutex_init(&gen.wait, NULL);
	gettimeofday(&gen.reftime, NULL);
	gen.firsttime = ((unsigned long)gen.reftime.tv_sec * 1000)
		+ ((unsigned long)gen.reftime.tv_usec / 1000);
	gen.firsttime -= 100;
	gen.mutex_forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * gen.philo_num);
	gen.threads = (pthread_t *)malloc(sizeof(pthread_t) * gen.philo_num);
	return (gen);
}

void	sleeping(t_philo *philo)
{
	if (philo->lst->running == 1)
	{
		pthread_mutex_unlock(philo->mutex_left);
		pthread_mutex_unlock(philo->mutex_right);
		pressftotalk(philo, 4);
	}
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_right);
	if (philo->lst->running == 1)
		pressftotalk(philo, 1);
	pthread_mutex_lock(philo->mutex_left);
	if (philo->lst->running == 1)
		pressftotalk(philo, 1);
}