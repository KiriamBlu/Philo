/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:40:34 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/03/02 00:04:51 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_finthread(t_gen *gen)
{
	pthread_mutex_unlock(&gen->wait);
	pthread_mutex_destroy(&gen->wait);
	free(gen->forks);
	free(gen->mutex_forks);
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
			return (1);
		if (i == 1 && aux > 200)
			return (1);
		if ((i == 2 || i == 3 || i == 4) && aux < 60)
			return (1);
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
		gen.eattime = (ft_atoi_special_l(argv[5]));
	pthread_mutex_init(&gen.wait, NULL);
	gettimeofday(&gen.reftime, NULL);
	gen.firsttime = ((unsigned long)gen.reftime.tv_sec * 1000)
		+ ((unsigned long)gen.reftime.tv_usec / 1000);
	gen.forks = ft_calloc(sizeof(int), gen.philo_num);
	gen.mutex_forks = ft_calloc(sizeof(pthread_mutex_t), gen.philo_num);
	gen.threads = ft_calloc(sizeof(pthread_t), gen.philo_num);
	return (gen);
}

void	sleeping(t_philo *philo)
{
	if (philo->lst->running == 1)
	{
		philo->lst->forks[philo->fork_right] = 0;
		philo->lst->forks[philo->fork_left] = 0;
		pressftotalk(philo, 4);
	}
}

void	pickfork(t_philo *philo)
{
	while (philo->count < 2 && philo->lst->running == 1)
	{
		pthread_mutex_lock(philo->mutex_right);
		if (philo->lst->running == 1
			&& philo->lst->forks[philo->fork_right] == 0)
		{
			philo->lst->forks[philo->fork_right] = 1;
			pressftotalk(philo, 1);
			philo->count++;
		}
		pthread_mutex_unlock(philo->mutex_right);
		usleep(100);
		pthread_mutex_lock(philo->mutex_left);
		if (philo->lst->running == 1
			&& philo->lst->forks[philo->fork_left] == 0)
		{
			philo->lst->forks[philo->fork_left] = 1;
			pressftotalk(philo, 1);
			philo->count++;
		}
		usleep(100);
		pthread_mutex_unlock(philo->mutex_left);
	}
	philo->count = 0;
}
