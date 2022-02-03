/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atois.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:37:09 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/01 18:01:39 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	forkinit(t_philo *philo, t_gen *gen, int i)
{
	philo[i].fork_left = i;
	if (i != gen->philo_num - 1)
		philo[i].fork_right = (i + 1);
	else
		philo[i].fork_right = 0;
	philo[i].eats = 0;
	philo[i].count = 0;
}

void	phinit(t_philo *philo, t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < gen->philo_num)
	{
		pthread_mutex_init(&gen->mutex_forks[i], NULL);
		gen->forks[i] = 0;
	}
	i = 0;
	while (i < gen->philo_num)
	{
		philo[i].mutex_left = &gen->mutex_forks[i];
		if (i != gen->philo_num - 1)
			philo[i].mutex_right = &gen->mutex_forks[i + 1];
		else
			philo[i].mutex_right = &gen->mutex_forks[0];
		forkinit(philo, gen, i);
		philo[i].lst = gen;
		philo[i].food = 0;
		philo[i].lasttime = philo[i].lst->firsttime;
		philo[i].index = i + 1;
		philo[i].deathstatus = 0;
		philo[i].thread = gen->threads[i];
		i++;
	}
}

int	ft_atoi_special(const char *str)
{
	int				i[2];
	unsigned long	nb;

	i[0] = 0;
	i[1] = 0;
	nb = 0;
	while (str[i[0]] == ' ' || str[i[0]] == '\n' || str[i[0]] == '\t' \
			|| str[i[0]] == '\f' || str[i[0]] == '\v' || str[i[0]] == '\r')
		i[0]++;
	if (str[i[0]] == '+' || str[i[0]] == '-')
		if (str[i[0]++] == '-')
			i[1] = 1;
	while (str[i[0]] >= '0' && str[i[0]] <= '9')
		nb = (nb * 10) + (str[i[0]++] - '0');
	if (i[1] != 0)
		return ((int)nb * -1);
	return ((int) nb);
}

unsigned long	ft_atoi_special_l(const char *str)
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
	return (nb);
}
