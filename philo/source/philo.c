/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:31:47 by jporta            #+#    #+#             */
/*   Updated: 2022/01/26 18:24:31 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	pressftotalk(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->lst->wait);
	if (i == 0 && philo->lst->running == 1)
		printf(COLOR_BLUE
			"%lu %d is thinking\n" COLOR_RESET, timestamp(philo), philo->index);
	else if (i == 1 && philo->lst->running == 1)
		printf(COLOR_YELLOW
			"%lu %d has taken a fork\n" COLOR_RESET,
			timestamp(philo), philo->index);
	else if (i == 3 && philo->lst->running == 1)
	{
		philo->eats++;
		printf(COLOR_MAGENTA
			"%lu %d is eating #%d\n" COLOR_RESET, timestamp(philo),
			philo->index, philo->eats);
	}
	else if (i == 4 && philo->lst->running == 1)
		printf(COLOR_CYAN
			"%lu %d is sleeping\n" COLOR_RESET, timestamp(philo), philo->index);
	else if (i == 5)
		printf(COLOR_RED
			"%lu %d died\n" COLOR_RESET, timestamp(philo), philo->index);
	pthread_mutex_unlock(&philo->lst->wait);
}

void	*managment_2(void *prueba)
{
	t_philo	*philo;

	philo = (t_philo *)prueba;
	philo->lasttime = philo->lst->firsttime;
	myusleep(100, philo);
	while (philo->lst->running == 1 && philo->eats < (int)philo->lst->eattime)
	{
		if (philo->index % 2 == 0)
			myusleep(1, philo);
		think(philo);
		getupdatetime(philo);
		if (philo->lst->running == 1)
			pressftotalk(philo, 3);
		myusleep(philo->lst->timetoeat, philo);
		sleeping(philo);
		myusleep(philo->lst->timetosleep, philo);
		if (philo->lst->running == 1)
		pressftotalk(philo, 0);
	}
	return (0);
}

void	*managment_1(void *prueba)
{
	t_philo	*philo;

	philo = (t_philo *)prueba;
	philo->lasttime = philo->lst->firsttime;
	myusleep(100, philo);
	while (philo->lst->running == 1)
	{
		if (philo->index % 2 == 0)
			myusleep(1, philo);
		think(philo);
		getupdatetime(philo);
		if (philo->lst->running == 1)
			pressftotalk(philo, 3);
		myusleep(philo->lst->timetoeat, philo);
		sleeping(philo);
		myusleep(philo->lst->timetosleep, philo);
		if (philo->lst->running == 1)
		pressftotalk(philo, 0);
	}
	return (0);
}

void	deathswitch(t_philo *philo, t_gen *gen)
{
	int				i;
	int				k;

	while (1)
	{
		k = 0;
		i = -1;
		while (++i < gen->philo_num)
		{
			k += philo[i].eats;
			if (philo[i].lst->deathtime < checktime(&philo[i]))
			{
				gen->running = 0;
				pressftotalk(&philo[i], 5);
				return ;
			}
		}
		if (((int)gen->eattime * gen->philo_num) == k && gen->eattime != 0)
		{
			gen->running = 0;
			return ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_gen		gen;
	t_philo		*philo;
	int			k;
	int			i;

	if (ft_errors(argc, argv) == 1)
	{
		printf("ERROR\n");
		return (0);
	}
	k = 0;
	gen = structinit(argv, argc);
	philo = (t_philo *)malloc(sizeof(t_philo) * gen.philo_num);
	phinit(philo, &gen);
	i = -1;
	if (argc == 5)
		while (++i < gen.philo_num)
			pthread_create(&philo[i].thread, NULL, managment_1, &philo[i]);
	else if (argc == 6)
		while (++i < gen.philo_num)
			pthread_create(&philo[i].thread, NULL, managment_2, &philo[i]);
	philo->lst->running = 1;
	deathswitch(philo, &gen);
	ft_finthread (&gen);
	return (0);
}
